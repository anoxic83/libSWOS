/*
MIT License

Copyright (c) [2019] [Anoxic] [anoxic83@gmail.com]

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
#include "swosdb.h"
#include <filesystem>
#include <thread>

namespace SWOS
{
  
//================== SWSPLAYER ============================

  SWSPlayer::SWSPlayer()
  {
    
  }
  bool SWSPlayer::Load(std::ifstream& ifs)
  {
    ifs.read((char*)&data,sizeof(SWSPlayerStruct));
    if (ifs)
      return true;
    else
      return false;
  }
  bool SWSPlayer::Save(std::ofstream& ofs)
  {
    ofs.write((const char*)&data, sizeof(SWSPlayerStruct));
    if (ofs)
      return true;
    else
      return false;
  }

  void SWSPlayer::SetName(const std::string &name)
  { 
    std::string str = name;
    for (auto & c: str) c = toupper(c);
    strcpy_s(data.name,23,str.c_str()); 
  }

  uint8_t SWSPlayer::GetAttributte(int attr, bool To7)
  {
    switch (attr)
    {
    case SWS_ATTRIBUTTE_PASSING:
      if (To7)
        return data.attXP.second & 0x7;
      else
        return data.attXP.second;
    case SWS_ATTRIBUTTE_SHOTING:
      if (To7)
        return data.attVH.first & 0x7;
      else
        return data.attVH.first;
    case SWS_ATTRIBUTTE_HEADING:
      if (To7)
        return data.attVH.second & 0x7;
      else
        return data.attVH.second;
    case SWS_ATTRIBUTTE_TACKLING:
      if (To7)
        return data.attTC.first & 0x7;
      else
        return data.attTC.first;
    case SWS_ATTRIBUTTE_BALLCONTROL:
      if (To7)
        return data.attTC.second & 0x7;
      else
        return data.attTC.second;
    case SWS_ATTRIBUTTE_SPEED:
      if (To7)
        return data.attSF.first & 0x7;
      else
        return data.attSF.first;
    case SWS_ATTRIBUTTE_FINISHING:
      if (To7)
        return data.attSF.second & 0x7;
      else
        return data.attSF.second;
    default:
      return 0;
      break;
    }
  }

  uint8_t SWSPlayer::GetAttributtesCalc()
  {
    uint8_t val = 0;
    for (int a=0;a<7;a++)
      val+=GetAttributte(a);
    return val;
  }
  uint8_t SWSPlayer::GetAttributtesCalcTo7()
  {
    uint8_t val = 0;
    for (int a=0;a<7;a++)
      val+=GetAttributte(a, true);
    return val;
  }

bool sortbysec(const std::pair<char,uint8_t> &a, 
              const std::pair<char,uint8_t> &b) 
{ 
    return (a.second < b.second); 
} 
  

  std::string SWSPlayer::GenAttributeStr()
  {
    int go = 0;
    std::vector<std::pair<char,uint8_t>> attb;
    switch (data.position.position)
    {
    // WING BACK
    case 1:
    case 2:
      attb.push_back(std::make_pair('F',GetAttributte(6,true)));
      attb.push_back(std::make_pair('C',GetAttributte(4,true)));
      attb.push_back(std::make_pair('H',GetAttributte(2,true)));
      attb.push_back(std::make_pair('V',GetAttributte(1,true)));
      attb.push_back(std::make_pair('P',GetAttributte(0,true)));
      if (GetAttributte(5,true) == GetAttributte(3,true))
      {
        if (data.value % 2 != 0)
        go++;
      }
      if (data.name[1] % 2 != 0)
        go++;
      if (data.name[2] % 2 != 0)
        go++;        
      if (go % 2 == 0)
      {
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      attb.push_back(std::make_pair('S',GetAttributte(5,true)));
      }
      else
      {
      attb.push_back(std::make_pair('S',GetAttributte(5,true)));
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      }
      break;
    // --------DEFENDER
    case 3:
      attb.push_back(std::make_pair('F',GetAttributte(6,true)));
      attb.push_back(std::make_pair('C',GetAttributte(4,true)));
      attb.push_back(std::make_pair('V',GetAttributte(1,true)));
      attb.push_back(std::make_pair('S',GetAttributte(5,true)));
      attb.push_back(std::make_pair('P',GetAttributte(0,true)));
      if (GetAttributte(3,true) == GetAttributte(2,true))
      {
        if (data.value % 2 != 0)
        go++;
      }
      if (data.name[1] % 2 != 0)
        go++;
      if (data.name[2] % 2 != 0)
        go++;        
      if (go % 2 == 0)
      {
      attb.push_back(std::make_pair('H',GetAttributte(2,true)));
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      }
      else
      {
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      attb.push_back(std::make_pair('H',GetAttributte(2,true)));
      }
      break;    
    // WINGERS
    case 4:
    case 5:
      attb.push_back(std::make_pair('V',GetAttributte(1,true)));
      attb.push_back(std::make_pair('F',GetAttributte(6,true)));
      attb.push_back(std::make_pair('H',GetAttributte(2,true)));
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      attb.push_back(std::make_pair('P',GetAttributte(0,true)));
      if (GetAttributte(4,true) == GetAttributte(5,true))
      {
        if (data.value % 2 != 0)
        go++;
      }
      if (data.name[1] % 2 != 0)
        go++;
      if (data.name[2] % 2 != 0)
        go++;        
      if (go % 2 == 0)
      {
      attb.push_back(std::make_pair('C',GetAttributte(4,true)));
      attb.push_back(std::make_pair('S',GetAttributte(5,true)));
      }
      else
      {
      attb.push_back(std::make_pair('S',GetAttributte(5,true)));
      attb.push_back(std::make_pair('C',GetAttributte(4,true)));
      }
      break;    
      // MIDFILERD
    case 6:
      attb.push_back(std::make_pair('F',GetAttributte(6,true)));
      attb.push_back(std::make_pair('S',GetAttributte(5,true)));
      attb.push_back(std::make_pair('V',GetAttributte(1,true)));
      attb.push_back(std::make_pair('H',GetAttributte(2,true)));
      attb.push_back(std::make_pair('C',GetAttributte(4,true)));
      if (GetAttributte(3,true) == GetAttributte(0,true))
      {
        if (data.value % 2 != 0)
        go++;
      }
      if (data.name[1] % 2 != 0)
        go++;
      if (data.name[2] % 2 != 0)
        go++;        
      if (go % 2 == 0)
      {
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      attb.push_back(std::make_pair('P',GetAttributte(0,true)));
      }
      else
      {
      attb.push_back(std::make_pair('P',GetAttributte(0,true)));
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      }
      break;  
      // ATTACKER
    case 7:
      attb.push_back(std::make_pair('T',GetAttributte(3,true)));
      attb.push_back(std::make_pair('P',GetAttributte(0,true)));
      attb.push_back(std::make_pair('C',GetAttributte(4,true)));
      attb.push_back(std::make_pair('V',GetAttributte(1,true)));
      attb.push_back(std::make_pair('S',GetAttributte(5,true)));
      if (GetAttributte(6,true) == GetAttributte(2,true))
      {
        if (data.value % 2 != 0)
        go++;
      }
      if (data.name[1] % 2 != 0)
        go++;
      if (data.name[2] % 2 != 0)
        go++;        
      if (go % 2 == 0)
      {
      attb.push_back(std::make_pair('H',GetAttributte(2,true)));
      attb.push_back(std::make_pair('F',GetAttributte(6,true)));
      }
      else
      {
      attb.push_back(std::make_pair('F',GetAttributte(6,true)));
      attb.push_back(std::make_pair('H',GetAttributte(2,true)));
      }
      break;      
    default:
      return std::string("");
      break;
    }
    std::sort(attb.begin(),attb.end(),sortbysec);
    std::reverse(attb.begin(), attb.end());
    std::string res = "";
    for (auto it=attb.begin(); it!=attb.end(); ++it)
    {
      res+= it->first;
    }

    
    return res.substr(0,3);
  }

//================== SWSTEAM ============================

  SWSTeam::SWSTeam()
  {

  }

  bool SWSTeam::Load(std::ifstream& ifs)
  {
    ifs.read((char*)&data,sizeof(SWSTeamStruct));
    if (!ifs)
      return false;
    bool res = false;
    for (int p=0;p<16;p++)
    {
      std::shared_ptr<SWSPlayer> pla = std::make_shared<SWSPlayer>();
      res = pla->Load(ifs);
      m_Players.push_back(pla);
    }
    return res;
  }
  bool SWSTeam::Save(std::ofstream& ofs)
  {
    ofs.write((const char*)&data, sizeof(SWSTeamStruct));
    if (!ofs)
      return false;
    bool res = false;
    for (int p=0;p<16;p++)
    {
      res = m_Players[p]->Save(ofs);
    }
    return res;
  }

  void SWSTeam::SetName(const std::string &name)
  { 
    std::string str = name;
    for (auto & c: str) c = toupper(c);
    strcpy_s(data.name,19,str.c_str()); 
  }

  std::shared_ptr<SWSPlayer> SWSTeam::GetPlayer(int no)
  {
    if (no >= 16)
      return nullptr;
    return m_Players[no];
  }

  uint16_t SWSTeam::GetAttributtesCalc()
  {
    uint16_t val = 0;
    for (int p=0; p<16; p++)
    {
      val += m_Players[p]->GetAttributtesCalc();
    }
    return val;
  }
  uint16_t SWSTeam::GetAttributtesCalcTo7()
  {
    uint16_t val = 0;
    for (int p=0; p<16; p++)
    {
      val += m_Players[p]->GetAttributtesCalcTo7();
    }
    return val;
  }

//================== SWSFILE ============================

  SWSFile::SWSFile()
  : m_Teamcount(0), m_Open(false), m_External(false)
  {
  }

  bool SWSFile::Load(const std::string& filename)
  {
    m_Filename = filename;
    std::ifstream ifs(filename, std::ios::binary);
    ifs.seekg(1,std::ios::beg);
    ifs.read((char*)&m_Teamcount,1);
    if (!ifs)
      return false;
    bool res = false;
    for (int t=0; t<m_Teamcount; t++)
    {
      std::shared_ptr<SWSTeam> tea = std::make_shared<SWSTeam>();
      res = tea->Load(ifs);
      m_Teams.push_back(tea);
    }
    m_Open = true;
    return res;
  }
  bool SWSFile::Save(const std::string& filename)
  {
    std::ofstream ofs(filename, std::ios::binary);
    ofs.write(0,1);
    ofs.write((const char*)m_Teamcount,1);
     if (!ofs)
      return false;
    bool res = false;
    for (int t=0; t<m_Teamcount; t++)
    {
      res = m_Teams[t]->Save(ofs);
    }
    return res;   
  }

  void SWSFile::FindPlayers(const std::string& name, std::vector< std::pair< std::pair< std::shared_ptr<SWSPlayer>, int>, std::shared_ptr<SWSTeam> >> & data)
  {
    int i = 0;
    for (auto t: m_Teams)
      for (int p=0; p<16; p++)
        if (t->GetPlayer(p)->GetName() == name)
        {
          i++;
          data.push_back(std::make_pair(std::make_pair(t->GetPlayer(p),i),t));
        }
  }


  SWSDivisionTeams_t SWSFile::GetDivisionCount()
  {
    for (int a=0; a<m_Teamcount;a++)
    {
      switch (m_Teams[a]->GetDivision())
      {
      case SWS_TEAM_PREMIER:
        m_DivisionCount.Premier++;
        break;
      case SWS_TEAM_FIRST:
        m_DivisionCount.First++;
        break;
      case SWS_TEAM_SECOND:
        m_DivisionCount.Second++;
        break;
        case SWS_TEAM_THIRD:
        m_DivisionCount.Third++;
        break;
      case SWS_TEAM_NONLEAGUE:
        m_DivisionCount.NonLeague++;
        break;      
      default:
        m_DivisionCount.NonLeague++;
        break;
      }
    }
    return m_DivisionCount;
  }

  std::shared_ptr<SWSTeam>SWSFile::GetTeam(int no)
  {
    if (no>=m_Teamcount)
      return nullptr;
    return m_Teams[no];
  }

// SWSDatabase

SWSDatabase::SWSDatabase(const std::string& path)
{
  m_DBpath = path;

}

bool SWSDatabase::LoadAllDatabase()
{
  const size_t size = std::extent<decltype(SWSTeamFileNames)>::value;

  bool res = false;
  for (int a=0; a<size; a++)
  {
    if (std::filesystem::exists(m_DBpath+SWSTeamFileNames[a]))
    {
      std::shared_ptr<SWSFile> swf = std::make_shared<SWSFile>();
      swf->SetFileName(SWSTeamFileNames[a]);
      swf->SetNationName(SWSTeamFileCoutries[a]);
      res = swf->Load(m_DBpath+SWSTeamFileNames[a]);
      m_TeamFiles.push_back(swf);
    }
  }
  return res;
}

void SWSDatabase::SaveAllDatabase()
{
  for (auto teams : m_TeamFiles)
    teams->Save(teams->GetFilename());
}


bool SWSDatabase::LoadSWSFile(int no)
{
  return m_TeamFiles[no]->Load(m_DBpath+m_TeamFiles[no]->GetFilename());
}

std::shared_ptr<SWSFile> SWSDatabase::GetSWSFile(int no)
{
  if (no>=GetFilesCount())
    return nullptr;
  return m_TeamFiles[no];
}

std::shared_ptr<SWSFile> SWSDatabase::AddSWSFile(const std::string& filename)
{
  std::shared_ptr<SWSFile> lsf = std::make_shared<SWSFile>();
  lsf->Load(filename);
  lsf->SetFileName(filename);
  lsf->SetExternal(true);
  m_TeamFiles.push_back(lsf);
  return lsf;
}

void SWSDatabase::FindPlayers(const std::string& name, std::vector< std::pair< std::pair< std::shared_ptr<SWSPlayer>, int>, std::shared_ptr<SWSTeam> >> & data)
{
  for (auto f : m_TeamFiles)
    f->FindPlayers(name,data);
}

std::vector< std::pair< std::pair< std::shared_ptr<SWSPlayer>, int>, std::shared_ptr<SWSTeam> >> SWSDatabase::FindPlayerDuplicates()
{
  std::vector< std::pair< std::pair< std::shared_ptr<SWSPlayer>, int>, std::shared_ptr<SWSTeam> >> tmp;
  for (auto f: m_TeamFiles)
    for (int t = 0; t < f->GetTeamCount(); t++)
      for (int p = 0; p < 16; p++)
      {     
        FindPlayers(f->GetTeam(t)->GetPlayer(p)->GetName(), tmp);
        //todo alldvv
      }
  return tmp;
}

} // namespace SWOS

SWOS::SWSDatabase* db;

void* CreateDatabase(const char* path)
{
  SWOS::SWSDatabase* db = new SWOS::SWSDatabase(std::string(path));
  return (void*)db;
}

void FreeDatabase(void* database)
{
  db = (SWOS::SWSDatabase*)database;
  delete db;
}

bool LoadAllDatabase(void* database)
{
  db = (SWOS::SWSDatabase*)database;
  return db->LoadAllDatabase();
}

int GetDatabaseCount(void* database)
{
  db = (SWOS::SWSDatabase*)database;
  return db->GetFilesCount();
}

void FindDuplicates(void* database)
{
  SWOS::SWSDatabase* db = (SWOS::SWSDatabase*)database;
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
  }
  std::cout << "Find "<< dup << " duplicated names. Press ENTER to exit.\n";
  ofs.close();
}

void SaveAllDatabase(void* database)
{
  db = (SWOS::SWSDatabase*)database;
  db->SaveAllDatabase();
}

bool AddFileToDatabase(void* database, const char* swsfile)
{
  db = (SWOS::SWSDatabase*)database;
  db->AddSWSFile(std::string(swsfile));
  return true;
}

bool GetSWSFileData(void* database, int fileno, SWOS::SWSFileStr_t* swsfile)
{
  db = (SWOS::SWSDatabase*)database;
  if ((fileno>=db->GetFilesCount())||(fileno<0))
    return false;
  SWOS::SWSFileStr_t* sf= new SWOS::SWSFileStr_t;
  sf->teamscount = db->GetSWSFile(fileno)->GetTeamCount();
  sf->swsfile = db->GetSWSFile(fileno).get();
  sf->dbteamno = fileno;
  swsfile = sf;
  return true;
}

int GetSWSTeamsCount(void* database, int fileno)
{
  db = (SWOS::SWSDatabase*)database;
  if ((fileno>=db->GetFilesCount())||(fileno<0))
    return -1;
  return db->GetSWSFile(fileno)->GetTeamCount();  
}

bool GetSWSTeamData(void* database, int fileno, int teamno, SWOS::SWSTeamStruct_t swsteam)
{
  db = (SWOS::SWSDatabase*)database;
  if ((fileno>=db->GetFilesCount()) || (fileno<0))
    return false;
  if ((teamno >= db->GetSWSFile(fileno)->GetTeamCount()) || (teamno < 0))
    return false;
  swsteam = db->GetSWSFile(fileno)->GetTeam(teamno)->GetRawData();
  return true;
}