from code_generator.cpp_generator import CppLanguageElement


class DoxyComment(CppLanguageElement):
    # Formatter = ANSICodeStyle

    availablePropertiesNames = {'style',
                                'is_static',
                                'is_extern',
                                'is_const',
                                'is_constexpr',
                                'initialization_value',
                                'documentation',
                                'is_class_member'} | CppLanguageElement.availablePropertiesNames

    # def __init__(self, filename, writer=None):
