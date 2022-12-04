#include <ftxui/dom/elements.hpp>  // for color, Fit, LIGHT, align_right, bold, DOUBLE
#include <ftxui/dom/table.hpp>      // for Table, TableSelection
#include <ftxui/screen/screen.hpp>  // for Screen
#include <iostream>                 // for endl, cout, ostream
#include <string>                   // for basic_string, allocator, string
#include <vector>                   // for vector
#include <stddef.h>
#include <stdint.h>

#include "ftxui/dom/node.hpp"  // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Cyan, Color::White, ftxui

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  using namespace ftxui;
   
  std::string buf(reinterpret_cast<const char*>(data), size);
  buf.push_back('\0');
  auto table = Table({
      {"Version", "Marketing name", "Release date", "API level", "Runtime"},
      {buf.c_str(), buf.c_str(), buf.c_str(), buf.c_str(), buf.c_str(),},
      {"4.0", "Ice Cream Sandwich", "October 19 2011", "15", "Dalvik"},
  });

  table.SelectAll().Border(LIGHT);

  // Add border around the first column.
  table.SelectColumn(0).Border(LIGHT);

  // Make first row bold with a double border.
  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(LIGHT);
  table.SelectRow(0).Border(DOUBLE);

  // Align right the "Release date" column.
  table.SelectColumn(2).DecorateCells(align_right);

  // Select row from the second to the last.
  auto content = table.SelectRows(1, -1);
  // Alternate in between 3 colors.
  content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
  content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
  content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

  auto document = table.Render();
  auto screen = Screen::Create(Dimension::Fit(document));
  Render(screen, document);
  screen.Print();
  std::cout << std::endl;

  return 0;
}

