import re
from itertools import tee, zip_longest

"""
(6, 9) [(1,4), (10,11)] -> false
(6, 9) [(1,4), (5,11)] -> true
"""
def strings_contain_item(item_idxs, strings_idxs):
    for idxs in strings_idxs:
        first, last = idxs[0], idxs[1]
        if item_idxs[0] > first and item_idxs[1] < last:
            return True
    return False

def remove_nums_in_strings(num_spans, string_spans):
    nums_not_nums = [item for item in num_spans if strings_contain_item(item, string_spans)]
    for item in nums_not_nums:
        num_spans.remove(item)
    return num_spans

def find_index(num, index_list):
    for idx, tup in enumerate(index_list):
        if num < tup[0]:
            return idx
    return len(list)

def merge_index_lists(first, second):
    combined_list: list = first
    for item in second:
        i = find_index(item[0], combined_list)
        combined_list.insert(i, item)
    return [item for tup in combined_list for item in tup]

def tokenize(msg: str):
    pattern_string = re.compile(r'X[0-9]+ \"[^\"]*\"')
    pattern_num = re.compile(r'U[0-9]+ [0-9]+')

    string_spans = [span.span() for span in pattern_string.finditer(msg)]
    num_spans = [span.span() for span in pattern_num.finditer(msg)]
    num_spans = remove_nums_in_strings(num_spans, string_spans)

    indices = merge_index_lists(num_spans, string_spans)
    indices.insert(0, 0)
    start, end = tee(indices)
    _ = next(end)
    parts = [msg[i:j].strip() for i,j in zip_longest(start, end)]

    print(parts)
    return parts

def convert(token: str):
    if token.startswith(U):
        pass
    elif token.startswith("X"):
        pass
    else:
        return token

def build_command(tokens):
    result: str = ""
    for tok in tokens:
        result += convert(tok)
    print(result)

def main():
    test = '31 013222 X32 "asd X32 " 00 X32 "asd U3 23 a" 00 U4 234 34 34'
    tokens = tokenize(test)
    build_command(tokens)

if __name__=="__main__":
    main()
