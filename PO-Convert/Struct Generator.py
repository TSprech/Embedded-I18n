import json
import re
from queue import LifoQueue as lifo
# import queue
import xmltodict

camel_split = re.compile(r'[A-Z](?:[a-z]+|[A-Z]*(?=[A-Z]|$))')


def camel_case_split(string: str, first_lower=True):
    if first_lower:
        string = string[0].capitalize() + string[1:]
    return re.findall(camel_split, string)


def title_case_merge(segments) -> str:
    return ''.join(segments)


def lower_underscore_merger(segments: list[str]) -> str:
    segments = [index.lower() for index in segments]
    return '_'.join(segments)


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


def replace(data, indent, running_list):
    if isinstance(data, dict):
        for key, value in data.items():
            if isinstance(value, dict) and isinstance(value[list(value.keys())[0]], str):
                running_list.append((key, value[list(value.keys())[0]]))
            elif isinstance(value, list):
                if isinstance(value[0], dict):
                    for item in value:
                        running_list.append((key, item[list(value[0].keys())[0]]))
                        running_list.append([])
                        replace(item, indent + 1, running_list[len(running_list) - 1])
                    continue
            else:
                if not key[0] == '@' and not key[0] == '#':
                    running_list.append(key)
            running_list.append([])
            replace(data[key], indent + 1, running_list[len(running_list) - 1])
    elif isinstance(data, list):
        for value in data:
            replace(value, indent, running_list)


def print_nested_list(input_list, indent):
    if type(input_list) is list:
        for item in input_list:
            print_nested_list(item, indent + 2)
    else:
        print(' ' * indent, end='')
        print(input_list)


def gen_structs(input_list, lifo_list):
    if type(input_list[0]) is str:
        print(f"struct {input_list[0]}")
        if type(input_list[1][0]) is str:
            print(f"  {input_list[1][0]}")
            gen_structs(input_list[1], lifo_list)
        elif type(input_list[1][0]) is tuple:
            print(f"  {input_list[1][0][0]} {input_list[1][0][1]}")
            gen_structs(input_list[1], lifo_list)
    elif type(input_list[0]) is tuple:
        gen_structs(input_list[1], lifo_list)


def remove_nested_list(listt):
    for index, value in enumerate(reversed(listt)):
        if isinstance(value, list) and value != []:
            remove_nested_list(value)
        elif isinstance(value, list) and len(value) == 0:
            listt.remove(value)


# with open(f'{path}/{language}.xml', 'rb') as general_locale:
#     xml_data = xmltodict.parse(general_locale)
#     data_list = list()
#     replace(xml_data, 0, data_list)
#
#     data_lifo = lifo()
#
#     remove_nested_list(data_list)
#
#     print_nested_list(data_list, 0)
#     print('\n\n')
#     gen_structs(data_list, data_lifo)


def indent_len(string: str):
    return len(string) - len(string.lstrip())


with open(f'{path}/{language}.xml', 'r', encoding='utf-8') as locale:
    lines = locale.readlines()  # Create the list of all lines in the file
    skip_lines = 0  # This will be what line the comment block ends on, so it can be skipped
    while '-->' not in lines[skip_lines]:
        skip_lines += 1  # Find the end of the comment block which is marked by --> NOTE: The valid data starts on the line after the comment block
    for line_num in range(skip_lines + 1, len(lines)):  # Iterate through all lines from the end of the comment block to the last line
        if '</' not in lines[line_num] and '/>' not in lines[line_num]:  # Make sure that the line being parsed is not a termination tag (or a tag without a terminator which ends with />)
            tag = re.findall(r'(?<=<).+?(?=[ >])', lines[line_num])[0]  # Parse the tag which resides between < and > for standard tag [eg. <date>] and < and (space) for a tag with attributes [eg. <date type="wide">]
            indent = indent_len(lines[line_num + 1])  # Get how indented the nested entry is, this means that the XML file has to be indented in accordance to the hierarchy to parse correctly
            end_line_num = line_num  # This will be the line that the termination tag is on [eg. if the tag <date> is on line 20 then this will equal whatever line </date> is on such as 100]
            while re.findall(r'(?<=<).+?(?=[ >])', lines[end_line_num])[0] != f'/{tag}':  # Keep going through lines until something matching </{tag}> is found
                end_line_num += 1

            print('\t' * indent + 'struct ' + tag + ' {')  # This is the struct definition

            for check_num in range(line_num, end_line_num):  # Next all the member variable names need to be found, and they will all be found between the tag line number and end tag line number found above
                if '</' not in lines[check_num] and indent_len(lines[check_num]) == indent:  # Check that line being checked is not an end tag and that it resides at the index indent number required
                    # var_entries.append(lines[check_num])
                    tag = re.findall(r'(?<=<).+?(?=[> ])', lines[check_num])[0]  # Next extract the tag that meets the above requirements as it will be a member variable
                    if r'="' in lines[check_num]:  # It has an attribute like type="wide"
                        # [tag, attribute] = lines[check_num].split('=')
                        # [tag, garbage] = tag.split(' ')
                        attribute = re.findall(r'(?<=").+?(?=")', lines[check_num])[0]  # Parse out the attribute it contains as it will serve as the member variable's name
                        print('\t' * indent + tag, end=' ')
                        print(attribute)
                    else:  # If it does not have an attribute, then it is just a tag and can simply be added
                        print('\t' * indent + tag)
                elif indent_len(lines[check_num]) == indent:  # This case is for 'variables' which are entries without any nested tags eg. <month type="1">Jan</month>
                    try:
                        print('\t' * (indent + 1) + re.findall(r'(?<=>).+?(?=<)', lines[check_num])[0])  # Extract the value to use as a placeholder (could also use key by replacing the > < with " ")
                    except IndexError:  # If there is a problem, just keep going, this is more for manual assistance than a requirement
                        continue
            print('\t' * indent + '};')  # By the time this is reached, all members variables have been found and added

            # print(indent)
            # print(lines[end_line_num])

# for key, value in xml_data.items():
#     print(key)
# key2, value2 = value.items()
# print(key2)
# for key2, value2 in value.items():
#     print(key2)

# current_dict = xml_data
# for auto in current_dict:
#     if isinstance(current_dict[auto], dict):
#         print(f"Would generate struct for: {auto}")
#         current_dict = current_dict[auto]

# print(print(json.dumps(xml_data, indent=2)))

# struct_data = lifo()  # A lifo is used because the data is presented hierarchically, however we generate structs from the most specific to most broad to avoid having to forward declare all of them
# for str_line in general_locale.readlines():
#     # if '<' in str_line and '>' in str_line:
#     if str_line.count('<') == 1 and str_line.count('>') == 1:  # Check if the str_line is a tag
#         directives = re.findall(r"(?<=<).+?(?=>)", str_line)[0]  # Extract everything between the < and >
#         struct_data.put(directives)  # Place the data in the LIFO
#
# inverted_data = lifo()  # This LIFO will serve to invert the reversal of the first LIFO as the first LIFO is iterated through
#
# last_data = None  # The more specific (deeper in hierarchy) data tag
# indent = 0
# while not struct_data.empty():  # Go through all the tags
#     current_data = struct_data.get()
#     if not current_data[0] == '/':  # If the popped data is not a tag termination (eg. </dates>)
#         indent -= 2
#         # print(' ' * indent + 'struct ' + title_case_merge(camel_case_split(current_data)) + ' {')
#         if last_data is not None:  # The first iteration through there is no prior data
#             # print(' ' * (indent - 2) + title_case_merge(camel_case_split(last_data)) + ' ' + lower_underscore_merger(camel_case_split(last_data)))
#             inverted_data.put(' ' * (indent - 2) + title_case_merge(camel_case_split(last_data)) + ' ' + lower_underscore_merger(camel_case_split(last_data)))  # The last data (the last struct generated) will have a member instance in the parent struct
#         inverted_data.put(' ' * indent + 'struct ' + title_case_merge(camel_case_split(current_data)) + ' {')  # Generate the parent struct
#     else:
#         indent += 2
#         # print(' ' * indent + '}')
#         inverted_data.put(' ' * indent + '}')  # If it is a tag termination, then close the brace
#     last_data = current_data
#
# # Print out the data
# while not inverted_data.empty():
#     print(inverted_data.get())
