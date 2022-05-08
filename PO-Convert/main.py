import polib
import re
import argparse


def extract_string_name(parser_indicator, comment_string):
    comment = re.search(parser_indicator + '(.+?)(?:$|\n)', comment_string)  # Get the string between the indicator and a newline or end of string
    return comment.group(1) if comment is not None else ''  # Check that some parser comment was actually extracted


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert PO files to header files')
    parser.add_argument('-c', '--comment', help='The comment string which indicates the start of a parser specific directive', default='/PARSER: ', required=False)
    args = vars(parser.parse_args())

    pofile = polib.pofile('sample.po')
    # print(pofile.translated_entries()[0].encoding)
    parser_comment = pofile.translated_entries()[0].comment
    custom_parser_indicator = args['comment']
    print(extract_string_name(custom_parser_indicator, parser_comment))
    print(pofile.translated_entries()[0].msgstr)
    msg = pofile.translated_entries()[0].msgstr
    print(len(msg))
    msg32 = msg.encode('utf-32')
