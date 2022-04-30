/**
* @file UTF8StressTest.hpp
* @author Original: Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/> - 2015-08-28 - CC BY 4.0
* @author Adapted for C++ Strings: TSprech
* @date 2022/04/17
* @copyright ©, 2022, TSprech - Apache License 2.0
* @warning This software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* @bug None (yet)
*/

#ifndef UTF8STRESSTEST_HPP
#define UTF8STRESSTEST_HPP

// This test file can help you examine, how your UTF-8 decoder handles
// various types of correct, malformed, or otherwise interesting UTF-8
// sequences. This file is not meant to be a conformance test. It does
// not prescribe any particular outcome. Therefore, there is no way to
// "pass" or "fail" this test file, even though the text does suggest a
// preferable decoder behaviour at some places. Its aim is, instead, to
// help you think about, and test, the behaviour of your UTF-8 decoder on a
// systematic collection of unusual inputs. Experience so far suggests
// that most first-time authors of UTF-8 decoders find at least one
// serious problem in their decoder using this file.
//
// The test lines below cover boundary conditions, malformed UTF-8
// sequences, as well as correctly encoded UTF-8 sequences of Unicode code
// points that should never occur in a correct UTF-8 file.
//
// According to ISO 10646-1:2000, sections D.7 and 2.3c, a device
// receiving UTF-8 shall interpret a "malformed sequence in the same way
// that it interprets a character that is outside the adopted subset" and
// "characters that are not within the adopted subset shall be indicated
// to the user" by a receiving device. One commonly used approach in
// UTF-8 decoders is to replace any malformed UTF-8 sequence by a
// replacement character (U+FFFD), which looks a bit like an inverted
// question mark, or a similar symbol. It might be a good idea to
// visually distinguish a malformed UTF-8 sequence from a correctly
// encoded Unicode character that is just not available in the current
// font but otherwise fully legal, even though ISO 10646-1 doesn't
// mandate this. In any case, just ignoring malformed sequences or
// unavailable characters does not conform to ISO 10646, will make
// debugging more difficult, and can lead to user confusion.
//
// Please check, whether a malformed UTF-8 sequence is (1) represented at
// all, (2) represented by exactly one single replacement character (or
// equivalent signal), and (3) the following quotation mark after an
// illegal UTF-8 sequence is correctly displayed, i.e. proper
// resynchronization takes place immediately after any malformed
// sequence. This file says "THE END" in the last line, so if you don't
// see that, your decoder crashed somehow before, which should always be
// cause for concern.
//
// All lines in this file are exactly 79 characters long (plus the line
// feed). In addition, all lines end with "|", except for the two test
// lines 2.1.1 and 2.2.1, which contain non-printable ASCII controls
// U+0000 and U+007F. If you display this file with a fixed-width font,
// these "|" characters should all line up in column 79 (right margin).
// This allows you to test quickly, whether your UTF-8 decoder finds the
// correct number of characters in every line, that is whether each
// malformed sequences is replaced by a single replacement character.
//
// Note that, as an alternative to the notion of malformed sequence used
// here, it is also a perfectly acceptable (and in some situations even
// preferable) solution to represent each individual byte of a malformed
// sequence with a replacement character. If you follow this strategy in
// your decoder, then please ignore the "|" column.

inline constexpr std::basic_string_view<char8_t>
operator""_sv8(const char8_t* str, size_t len) noexcept {
  return std::basic_string_view<char8_t>{str, len};
}

namespace utf8stress {
  // 2  Boundary condition test cases
  // 2.1  First possible sequence of a certain length
  constexpr std::array first_possible_sequence_of_a_certain_length = {
      u8"\x00"_sv8,                     // 2.1.1  1 byte  (U-00000000)
      u8"\xC2\x80"_sv8,                 // 2.1.2  2 bytes (U-00000080)
      u8"\xE0\xA0\x80"_sv8,             // 2.1.3  3 bytes (U-00000800)
      u8"\xF0\x90\x80\x80"_sv8,         // 2.1.4  4 bytes (U-00010000)
      u8"\xF8\x88\x80\x80\x80"_sv8,     // 2.1.5  5 bytes (U-00200000)
      u8"\xFC\x84\x80\x80\x80\x80"_sv8  // 2.1.6  6 bytes (U-04000000)
  };

  // 2.2  Last possible sequence of a certain length
  constexpr std::array last_possible_sequence_of_a_certain_length = {
      u8"\x7f"_sv8,                      // 2.2.1  1 byte  (U-0000007F)
      u8"\xDF\xBF"_sv8,                  // 2.2.2  2 bytes (U-000007FF)
      u8"\xEF\xBF\xBF"_sv8,              // 2.2.3  3 bytes (U-0000FFFF)
      u8"\xF7\xBF\xBF\xBF"_sv8,          // 2.2.4  4 bytes (U-001FFFFF)
      u8"\xFB\xBF\xBF\xBF\xBF"_sv8,      // 2.2.5  5 bytes (U-03FFFFFF)
      u8"\xFD\xBF\xBF\xBF\xBF\xBF"_sv8,  // 2.2.6  6 bytes (U-7FFFFFFF)
  };

  // 2.3  Other boundary conditions
  constexpr std::array other_boundary_conditions = {
      u8"\xED\x9F\xBF"_sv8,      // 2.3.1  U-0000D7FF = ed 9f bf
      u8"\xEE\x80\x80"_sv8,      // 2.3.2  U-0000E000 = ee 80 80
      u8"\xEF\xBF\xBD"_sv8,      // 2.3.3  U-0000FFFD = ef bf bd
      u8"\xF4\x8F\xBF\xBF"_sv8,  // 2.3.4  U-0010FFFF = f4 8f bf bf
      u8"\xF4\x90\x80\x80"_sv8   // 2.3.5  U-00110000 = f4 90 80 80
  };

  // 3 Malformed sequences
  // 3.1  Unexpected continuation bytes
  constexpr std::array unexpected_continuation_bytes = {
      u8"\x80"_sv8,                         // 3.1.1  First continuation byte 0x80
      u8"\xBF"_sv8,                         // 3.1.2  Last  continuation byte 0xbf
      u8"\x80\xBF"_sv8,                     // 3.1.3  2 continuation bytes
      u8"\x80\xBF\x80"_sv8,                 // 3.1.4  3 continuation bytes
      u8"\x80\xBF\x80\xBF"_sv8,             // 3.1.5  4 continuation bytes
      u8"\x80\xBF\x80\xBF\x80"_sv8,         // 3.1.6  5 continuation bytes
      u8"\x80\xBF\x80\xBF\x80\xBF"_sv8,     // 3.1.7  6 continuation bytes
      u8"\x80\xBF\x80\xBF\x80\xBF\x80"_sv8  // 3.1.8  7 continuation bytes
  };

  // 3.1.9  Sequence of all 64 possible continuation bytes (0x80-0xbf)
  constexpr std::array all_continuation_bytes = {u8"\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF"_sv8};

  // 3.2  Lonely start characters
  // 3.2.1  All 32 first bytes of 2-byte sequences (0xc0-0xdf), each followed by a space character
  constexpr std::array all_first_2_byte_sequences = {u8"\xC0 \xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 \xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF \xD0 \xD1 \xD2 \xD3 \xD4 \xD5 \xD6 \xD7 \xD8 \xD9 \xDA \xDB \xDC \xDD \xDE \xDF "_sv8};

  // 3.2.2  All 16 first bytes of 3-byte sequences (0xe0-0xef), each followed by a space character
  constexpr std::array all_first_3_byte_sequences = {u8"\xE0 \xE1 \xE2 \xE3 \xE4 \xE5 \xE6 \xE7 \xE8 \xE9 \xEA \xEB \xEC \xED \xEE \xEF "_sv8};

  // 3.2.3  All 8 first bytes of 4-byte sequences (0xf0-0xf7), each followed by a space character
  constexpr std::array all_first_4_byte_sequences = {u8"\xF0 \xF1 \xF2 \xF3 \xF4 \xF5 \xF6 \xF7 "_sv8};

  // 3.2.4  All 4 first bytes of 5-byte sequences (0xf8-0xfb), each followed by a space character
  constexpr std::array all_first_5_byte_sequences = {u8"\xF8 \xF9 \xFA \xFB "_sv8};

  // 3.2.5  All 2 first bytes of 6-byte sequences (0xfc-0xfd), each followed by a space character
  constexpr std::array all_first_6_byte_sequences = {u8"\xFC \xFD "_sv8};

  // 3.3  Sequences with last continuation byte missing
  // All bytes of an incomplete sequence should be signalled as a single malformed sequence, i.e., you should see only a single replacement character in each of the next 10 tests. (Characters as in section 2)
  constexpr std::array last_continuation_byte_missing = {
      u8"\xC0"_sv8,                  // 3.3.1  2-byte sequence with last byte missing (U+0000)
      u8"\xE0\x80"_sv8,              // 3.3.2  3-byte sequence with last byte missing (U+0000)
      u8"\xF0\x80\x80"_sv8,          // 3.3.3  4-byte sequence with last byte missing (U+0000)
      u8"\xF8\x80\x80\x80"_sv8,      // 3.3.4  5-byte sequence with last byte missing (U+0000)
      u8"\xFC\x80\x80\x80\x80"_sv8,  // 3.3.5  6-byte sequence with last byte missing (U+0000)
      u8"\xDF"_sv8,                  // 3.3.6  2-byte sequence with last byte missing (U-000007FF)
      u8"\xEF\xBF"_sv8,              // 3.3.7  3-byte sequence with last byte missing (U-0000FFFF)
      u8"\xF7\xBF\xBF"_sv8,          // 3.3.8  4-byte sequence with last byte missing (U-001FFFFF)
      u8"\xFB\xBF\xBF\xBF"_sv8,      // 3.3.9  5-byte sequence with last byte missing (U-03FFFFFF)
      u8"\xFD\xBF\xBF\xBF\xBF"_sv8   // 3.3.10 6-byte sequence with last byte missing (U-7FFFFFFF)
  };

  // 3.4  Concatenation of incomplete sequences
  // All the 10 sequences of 3.3 concatenated, you should see 10 malformed sequences being signalled:
  constexpr std::array concatination_of_incomplete_sequences = {u8"\xC0\xE0\x80\xF0\x80\x80\xF8\x80\x80\x80\xFC\x80\x80\x80\x80\xDF\xEF\xBF\xF7\xBF\xBF\xFB\xBF\xBF\xBF\xFD\xBF\xBF\xBF\xBF"_sv8};

  // 3.5  Impossible bytes
  // The following two bytes cannot appear in a correct UTF-8 string
  constexpr std::array impossible_bytes = {
      u8"\xFE"_sv8,             // 3.5.1  fe
      u8"\xFF"_sv8,             // 3.5.2  ff
      u8"\xFE\xFE\xFF\xFF"_sv8  // 3.5.3  fe fe ff ff
  };

  // 4 Overlong sequences
  // The following sequences are not malformed according to the letter of
  // the Unicode 2.0 standard. However, they are longer then necessary and
  // a correct UTF-8 encoder is not allowed to produce them. A "safe UTF-8
  // decoder" should reject them just like malformed sequences for two
  // reasons: (1) It helps to debug applications if overlong sequences are
  // not treated as valid representations of characters, because this helps
  // to spot problems more quickly. (2) Overlong sequences provide
  // alternative representations of characters, that could maliciously be
  // used to bypass filters that check only for ASCII characters. For
  // instance, a 2-byte encoded line feed (LF) would not be caught by a
  // line counter that counts only 0x0a bytes, but it would still be
  // processed as a line feed by an unsafe UTF-8 decoder later in the
  // pipeline. From a security point of view, ASCII compatibility of UTF-8
  // sequences means also, that ASCII characters are *only* allowed to be
  // represented by ASCII bytes in the range 0x00-0x7f. To ensure this
  // aspect of ASCII compatibility, use only "safe UTF-8 decoders" that
  // reject overlong UTF-8 sequences for which a shorter encoding exists.

  // 4.1 Examples of an overlong ASCII character
  // With a safe UTF-8 decoder, all of the following five overlong
  // representations of the ASCII character slash ("/") should be rejected
  // like a malformed UTF-8 sequence, for instance by substituting it with
  // a replacement character. If you see a slash below, you do not have a
  // safe UTF-8 decoder!

  constexpr std::array overlong_ascii_character = {
      u8"\xC0\xAF"_sv8,                 // 4.1.1 U+002F = c0 af
      u8"\xE0\x80\xAF"_sv8,             // 4.1.2 U+002F = e0 80 af
      u8"\xF0\x80\x80\xAF"_sv8,         // 4.1.3 U+002F = f0 80 80 af
      u8"\xF0\x80\x80\x80\xAF"_sv8,     // 4.1.4 U+002F = f8 80 80 80 af
      u8"\xF0\x80\x80\x80\x80\xAF"_sv8  // 4.1.5 U+002F = fc 80 80 80 80 af
  };

  // 4.2 Maximum overlong sequences
  // Below you see the highest Unicode value that is still resulting in an
  // overlong sequence if represented with the given number of bytes. This
  // is a boundary test for safe UTF-8 decoders. All five characters should
  // be rejected like malformed UTF-8 sequences.

  constexpr std::array maximum_overlong_sequences = {
      u8"\xC1\xBF"_sv8,                 // 4.2.1  U-0000007F = c1 bf
      u8"\xE0\x9F"_sv8,                 // 4.2.2  U-000007FF = e0 9f bf
      u8"\xF0\x8F\xBF\xBF"_sv8,         // 4.2.3  U-0000FFFF = f0 8f bf bf
      u8"\xF8\x87\xBF\xBF\xBF"_sv8,     // 4.2.4  U-001FFFFF = f8 87 bf bf bf
      u8"\xFC\x83\xBF\xBF\xBF\xBF"_sv8  // 4.2.5  U-03FFFFFF = fc 83 bf bf bf bf
  };

  // 4.3 Overlong representation of the NUL character
  // The following five sequences should also be rejected like malformed
  // UTF-8 sequences and should not be treated like the ASCII NUL
  // character.

  constexpr std::array overlong_nul_character = {
      u8"\xC0\x80"_sv8,                 // 4.3.1  U+0000 = c0 80
      u8"\xE0\x80\x80"_sv8,             // 4.3.2  U+0000 = e0 80 80
      u8"\xF0\x80\x80\x80"_sv8,         // 4.3.3  U+0000 = f0 80 80 80
      u8"\xF8\x80\x80\x80\x80"_sv8,     // 4.3.4  U+0000 = f8 80 80 80 80
      u8"\xFC\x80\x80\x80\x80\x80"_sv8  // 4.3.5  U+0000 = fc 80 80 80 80 80
  };

  // 5 Illegal code positions

  // The following UTF-8 sequences should be rejected like malformed
  // sequences, because they never represent valid ISO 10646 characters and
  // a UTF-8 decoder that accepts them might introduce security problems
  // comparable to overlong UTF-8 sequences.

  // 5.1 Single UTF-16 surrogates
  constexpr std::array single_utf16_surrogates = {
      u8"\xED\xA0\x80"_sv8,  // 5.1.1  U+D800 = ed a0 80
      u8"\xED\xAD\xBF"_sv8,  // 5.1.2  U+DB7F = ed ad bf
      u8"\xED\xAE\x80"_sv8,  // 5.1.3  U+DB80 = ed ae 80
      u8"\xED\xAF\xBF"_sv8,  // 5.1.4  U+DBFF = ed af bf
      u8"\xED\xB0\x80"_sv8,  // 5.1.5  U+DC00 = ed b0 80
      u8"\xED\xBE\x80"_sv8,  // 5.1.6  U+DF80 = ed be 80
      u8"\xED\xBF\xBF"_sv8   // 5.1.7  U+DFFF = ed bf bf
  };

  // 5.2 Paired UTF-16 surrogates
  constexpr std::array paired_utf16_surrogates = {
      u8"\xED\xA0\x80\xED\xB0\x80"_sv8,  // 5.2.1  U+D800 U+DC00 = ed a0 80 ed b0 80
      u8"\xED\xA0\x80\xED\xBF\xBF"_sv8,  // 5.2.2  U+D800 U+DFFF = ed a0 80 ed bf bf
      u8"\xED\xAD\xBF\xED\xB0\x80"_sv8,  // 5.2.3  U+DB7F U+DC00 = ed ad bf ed b0 80
      u8"\xED\xAD\xBF\xED\xBF\xBF"_sv8,  // 5.2.4  U+DB7F U+DFFF = ed ad bf ed bf bf
      u8"\xED\xAE\x80\xED\xB0\x80"_sv8,  // 5.2.5  U+DB80 U+DC00 = ed ae 80 ed b0 80
      u8"\xED\xAE\x80\xED\xBF\xBF"_sv8,  // 5.2.6  U+DB80 U+DFFF = ed ae 80 ed bf bf
      u8"\xED\xAF\xBF\xED\xB0\x80"_sv8,  // 5.2.7  U+DBFF U+DC00 = ed af bf ed b0 80
      u8"\xED\xAF\xBF\xED\xBF\xBF"_sv8   // 5.2.8  U+DBFF U+DFFF = ed af bf ed bf bf
  };

  // 5.3 Noncharacter code positions

  // The following "noncharacters" are "reserved for internal use" by
  // applications, and according to older versions of the Unicode Standard
  // "should never be interchanged". Unicode Corrigendum #9 dropped the
  // latter restriction. Nevertheless, their presence in incoming UTF-8 data
  // can remain a potential security risk, depending on what use is made of
  // these codes subsequently. Examples of such internal use:
  //
  //  - Some file APIs with 16-bit characters may use the integer value -1
  //    = U+FFFF to signal an end-of-file (EOF) or error condition.
  //
  //  - In some UTF-16 receivers, code point U+FFFE might trigger a
  //    byte-swap operation (to convert between UTF-16LE and UTF-16BE).
  //
  // With such internal use of noncharacters, it may be desirable and safer
  // to block those code points in UTF-8 decoders, as they should never
  // occur legitimately in incoming UTF-8 data, and could trigger unsafe
  // behaviour in subsequent processing.

  // Particularly problematic noncharacters in 16-bit applications:
  constexpr std::array problematic_noncharacters = {
      u8"\xEF\xBF\xBE"_sv8,  // 5.3.1  U+FFFE = ef bf be
      u8"\xEF\xBF\xBF"_sv8   // 5.3.2  U+FFFF = ef bf bf
  };

  // Other noncharacters:
  constexpr std::array other_noncharacters = {
      u8"\xEF\xB7\x90\xEF\xB7\x91\xEF\xB7\x92\xEF\xB7\x93\xEF\xB7\x94\xEF\xB7\x95\xEF\xB7\x96\xEF\xB7\x97\xEF\xB7\x98\xEF\xB7\x99\xEF\xB7\x9A\xEF\xB7\x9B\xEF\xB7\x9C\xEF\xB7\x9D\xEF\xB7\x9E\xEF\xB7\x9F\xEF\xB7\xA0\xEF\xB7\xA1\xEF\xB7\xA2\xEF\xB7\xA3\xEF\xB7\xA4\xEF\xB7\xA5\xEF\xB7\xA6\xEF\xB7\xA7\xEF\xB7\xA8\xEF\xB7\xA9\xEF\xB7\xAA\xEF\xB7\xAB\xEF\xB7\xAC\xEF\xB7\xAD\xEF\xB7\xAE\xEF\xB7\xAF"_sv8  // 5.3.3  U+FDD0 .. U+FDEF
  };

  constexpr std::array other_noncharacters_cont = {
      u8"\xF0\x9F\xBF\xBE\xF0\x9F\xBF\xBF\xF0\xAF\xBF\xBE\xF0\xAF\xBF\xBF\xF0\xBF\xBF\xBE\xF0\xBF\xBF\xBF\xF1\x8F\xBF\xBE\xF1\x8F\xBF\xBF\xF1\x9F\xBF\xBE\xF1\x9F\xBF\xBF\xF1\xAF\xBF\xBE\xF1\xAF\xBF\xBF\xF1\xBF\xBF\xBE\xF1\xBF\xBF\xBF\xF2\x8F\xBF\xBE\xF2\x8F\xBF\xBF\xF2\x9F\xBF\xBE\xF2\x9F\xBF\xBF\xF2\xAF\xBF\xBE\xF2\xAF\xBF\xBF\xF2\xBF\xBF\xBE\xF2\xBF\xBF\xBF\xF3\x8F\xBF\xBE\xF3\x8F\xBF\xBF\xF3\x9F\xBF\xBE\xF3\x9F\xBF\xBF\xF3\xAF\xBF\xBE\xF3\xAF\xBF\xBF\xF3\xBF\xBF\xBE\xF3\xBF\xBF\xBF\xF4\x8F\xBF\xBE\xF4\x8F\xBF\xBF"_sv8  // 5.3.4  U+nFFFE U+nFFFF (for n = 1..10)
  };
}  // namespace utf8stress

#endif  // UTF8STRESSTEST_HPP
