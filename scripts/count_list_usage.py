#!/usr/bin/python
import operator
import re
import sys
import subprocess


LIST_HEADER = 'include/list.h'


def print_usage():
    print('count_list_usage.py: counting list usage in Linux kernel')
    print('')
    print('Usage:')
    print('\tcount_list_usage.py kernel_source_path')
    print('')


def read_list_header():
    with open(LIST_HEADER) as f:
        for i in f.readlines():
            m = re.search(r'(list_|LIST_|INIT_|hlist_)\w*\(', i)
            if m:
                yield m.group()


def grep_in_kernel_source_and_wc(source_path, method_name):
    p = subprocess.Popen(['grep', '-r', source_path, '--include', '*.h',
                          '--include', '*.c', '-e', f'{method_name}'],
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    return len(out.decode('utf-8').split('\n'))


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print_usage()
        exit()

    d = {}
    for method in read_list_header():
        if method not in d:
            print(method)
            count = grep_in_kernel_source_and_wc(sys.argv[1], method)
            d[method] = count

    for method, count in sorted(d.items(), key=operator.itemgetter(1), reverse=True):
        print(f'{count: 5d}, {method}')
