#include <iostream>
#include <memory>
#include <swosdb.h>
#include <fstream>
#include <filesystem>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Syntax: finddupl <TEAMFILE>\n";
    return 1;
  }
  std::string filename(argv[1]);
  if (!std::filesystem::exists(filename))
  {
    std::cout << "File <"<< filename <<"> not found.\n";
    return 2;
  }
  std::vector< std::pair< std::pair< std::shared_ptr<SWOS::SWSPlayer>, int>, std::shared_ptr<SWOS::SWSTeam> >> tmp;
  std::unique_ptr<SWOS::SWSFile> m_File = std::make_unique<SWOS::SWSFile>();
  m_File->Load(filename);
  for (int t = 0; t < m_File->GetTeamCount(); t++)
    for (int p = 0; p < 16; p++)
    {     
      m_File->FindPlayers(m_File->GetTeam(t)->GetPlayer(p)->GetName(), tmp);
    }
  
  std::ofstream ofs(filename+"-dupl.txt");
  for (auto t: tmp)
  {
    ofs << t.first.second << "::" << t.first.first->GetName() << "<--->" << t.second->GetName() << "\n";
  }
  ofs.close();
  return 0;
}