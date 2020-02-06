/*
MIT License

Copyright (c) [2019-2020] [Anoxic] [anoxic83@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <iostream>
#include "swosdb.h"
#include <memory>
#include <fstream>

int main(int argc, char** argv)
{
  std::cout << "SWS - Duplicate Finder v. 0.1.2\n";
  std::cout << "(c)2020 AnoXic. MIT license.\n";
  bool prinscr = false;

  if (argc>1)
    if (strcmp(argv[1],"-p") || strcmp(argv[1],"-P"))
      prinscr = true;

  std::unique_ptr<SWOS::SWSDatabase> db = std::make_unique<SWOS::SWSDatabase>("DATA/");
  db->LoadAllDatabase();
  std::cout << "Files loaded: " << db->GetFilesCount() << "\n";
  for (int x=0; x<db->GetFilesCount();x++)
  {
    std::cout << db->GetSWSFile(x)->GetFilename() << "::" << db->GetSWSFile(x)->GetNationName() << "\n";
  }
  std::cout << "Searching...\n";
  std::vector< std::pair< std::pair< std::shared_ptr<SWOS::SWSPlayer>, int>, std::shared_ptr<SWOS::SWSTeam> >> tmp = db->FindPlayerDuplicates();
  std::vector< std::pair< std::pair< std::shared_ptr<SWOS::SWSPlayer>, int>, std::shared_ptr<SWOS::SWSTeam> >> duplic;
  int dup = 0;
  for (auto it = tmp.begin(); it != tmp.end(); ++it)
  {
    if (it->first.second == 2)
    {
      duplic.push_back(*(it-1));
      duplic.push_back(*it);
      dup++;
    }
    if (it->first.second > 2)
    {
      duplic.push_back(*it);
    }

  }
  std::ofstream ofs("duplicates.txt");
  for (auto t: duplic)
  {
    ofs << t.first.second << " :: " << t.first.first->GetName() << " <---> " << t.second->GetName() << "\n";
    if (prinscr)
      std::cout << t.first.second << " :: " << t.first.first->GetName() << " <---> " << t.second->GetName() << "\n";
  }
  std::cout << "Find "<< dup << " duplicated names. Press ENTER to exit.\n";
  ofs.close();
  std::cin.get();
  return 0;
}