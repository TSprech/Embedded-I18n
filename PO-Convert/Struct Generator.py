import argparse
import re
import xmltodict


def find_locale_point(data, *argv):
    """
    Finds locale data inside a CLDR XML file.
    :param data: A list of file objects in decreasing specificity | eg. [en_US, en].
    :param argv: The series of tags and attributes which specify the location of the desired data | eg. 'delimiters', 'quotationStart'.
    :returns: The data found at the specified tag/attribute path.
    """
    for file in data:
        try:  # Try to find the data in more specific files and move to more general files in accordance with the search_order list
            result = file  # Result will be the value found at the specified XML category
            for arg in argv:
                if arg[0] == '@':  # A string starting with an @ sign means that it is an attribute, so a search must be done to see where it is
                    key, attr = arg.split('=')
                    if isinstance(result, list):
                        result = next((item for item in result if item[key] == attr), None)  # Find the dictionary which contains the attribute value
                    # If it is already a dict, do nothing, as there is no need to iterate through multiple lists to see which one has the right attribute
                else:
                    try:
                        result = result[arg]  # If it is not an attribute, then it is likely a dictionary, so it can just be indexed into
                    except TypeError:
                        raise KeyError  # If however it was not a dictionary, then there is some other issue (most likely not a locale specific entry for it) so skip to the next search level
            return result  # If it successfully completed the above for loop, then the data was found and it can be returned
        except KeyError:  # This most likely means that the locale data is not specified in the specific XML file, so proceed to the general XML file
            continue


def write_locale_data(data: str, file):
    if file is None:
        print(data)
    else:
        file.write(data + '\n')


# url = args['url']
path = r"C:/Users/treys/OneDrive/Downloads/cldr/41.0/common/main"
locale_full = r'en_US'
language = 'en'  # Get the language from the first couple letters before the underscore in the locale name

# if output == 'print':
#     outfile = None
# else:
#     outfile = open(output, 'w', encoding='utf-8')

import queue

with open(f'{path}/{language}.xml', 'r', encoding='utf-8') as general_locale:
    for str_line in general_locale.readlines():
        # if '<' in str_line and '>' in str_line:
        if str_line.count('<') == 1 and str_line.count('>') == 1 and str_line.count('</') == 0:
            directives = re.findall(r"(?<=<).+?(?=>)", str_line)[0]  # Extract everything between the two ~
            print(' ' * (len(str_line) - len(str_line.lstrip())) + directives)
            
