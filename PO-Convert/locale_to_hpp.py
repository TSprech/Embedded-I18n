import argparse
import re
import xmltodict


def find_locale_point(data, *argv):
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


parser = argparse.ArgumentParser(description='Convert PO files to header files')
# parser.add_argument('-u', '--url',
#                     help = 'The url to the "main" folder in the cldr repo',
#                     required = True)
parser.add_argument('-p', '--path',
                    help='The path to the "main" folder in the cldr download',
                    required=True)
parser.add_argument('-l', '--locale',
                    help='The locale name',
                    required=True)
parser.add_argument('--hex',
                    help='Export the extracted data in hex format',
                    action='store_true')
args = vars(parser.parse_args())

# url = args['url']
path = args['path']
locale_full = args['locale']
language = args['locale'].split('_')[0]  # Get the language from the first couple letters before the underscore in the locale name
hex_format = args['hex']

with open(f'{path}/{language}.xml', 'rb') as general_locale:
    general_locale_map = xmltodict.parse(general_locale, encoding='UTF-8', xml_attribs=True)['ldml']
    with open(f'{path}/{locale_full}.xml', 'rb') as specific_locale:
        specific_locale_map = xmltodict.parse(specific_locale, encoding='UTF-8', xml_attribs=True)['ldml']
        search_order = [specific_locale_map, general_locale_map]  # These files should be in order from most specific (eg en_US) to least specific (eg en)

        test_file = open('HeaderFormatter', 'r')  # Read in the format file
        for str_line in test_file.readlines():
            directives = re.findall(r"(?<=~).+?(?=~)", str_line)[0]  # Extract everything between the two ~
            composition = f"found_char = find_locale_point(search_order, {directives})"  # Build a function call in the string which assigns a variable to the returned value
            exec(composition)  # Execute the string as code
            if hex_format:  # If the output is in hex representation
                if isinstance(found_char, str):  # Make sure it is a string as it could be a dict if there is draft data in CLDR
                    found_char = found_char.encode('utf-8')  # Hex requires utf-8 byte string representation
                    # found_char = '\\x' + '\\x'.join("{:02x}".format(ord(c)) for c in found_char)
                    found_char = '\\x' + '\\x'.join("{:02x}".format(c) for c in found_char)  # Join all the bytes with the hex string prefix
            line_start = re.findall(r".+?(?=~)", str_line)[0]  # Extract everything before the first ~
            line_end = re.findall(r"(?<='~).+?(?:$|\n)", str_line)[0]  # Extract everything from '~ to the end of the line TODO: Split it instead
            full_line = f'{line_start}"{str(found_char)}"{line_end}'  # Concatenate all the string portions together
            print(full_line)
