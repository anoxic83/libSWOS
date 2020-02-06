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
#pragma once
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <functional>
#include "swoscore.h"

namespace SWOS
{

// Multi Position-Skin Cards??
struct SWSAPI SWSMulti
{
  uint8_t unused : 3;
  uint8_t skin : 2;
  uint8_t position : 3;
};

typedef SWSMulti SWSAPI SWSMulti_t;

struct SWSAPI SWSAttributte
{
  uint8_t second : 4;
  uint8_t first: 4;
};

typedef SWSAttributte SWSAPI SWSAttributte_t;

struct SWSAPI SWSKit
{
  uint8_t type;
  uint8_t shirt_colA;
  uint8_t shirt_colB;
  uint8_t short_col;
  uint8_t socks_col;
} __attribute__((packed));

typedef SWSKit SWSAPI SWSKit_t;

struct SWSAPI SWSPlayerStruct
{
  uint8_t nationality;
  uint8_t res0;
  uint8_t number;
  char name[23];
  SWSMulti_t position;
  uint8_t res1;
  SWSAttributte_t attXP;
  SWSAttributte_t attVH;
  SWSAttributte_t attTC;
  SWSAttributte_t attSF;
  uint8_t value;
  uint8_t careerdta[5];
} __attribute__((packed));

struct SWSAPI SWSTeamStruct
{
  uint8_t nation;
  uint8_t number;
  uint16_t swsgenno;
  uint8_t res0;
  char name[19];
  uint8_t tactic;
  uint8_t division;
  SWSKit_t homekit;
  SWSKit_t awaykit;
  char coachname[24];
  uint8_t playerpos[16];
} __attribute__((packed));

typedef SWSPlayerStruct SWSAPI SWSPlayerStruct_t;

typedef SWSTeamStruct SWSAPI SWSTeamStruct_t;

struct SWSAPI SWSDivisionTeams
{
  uint8_t Premier;
  uint8_t First;
  uint8_t Second;
  uint8_t Third;
  uint8_t NonLeague;
};

typedef SWSDivisionTeams SWSAPI SWSDivisionTeams_t;

class SWSAPI SWSPlayer
{
  public:
    SWSPlayer();
    virtual ~SWSPlayer() = default;
    bool Load(std::ifstream& ifs);
    bool Save(std::ofstream& ofs);
    std::string GetName() { return std::string(data.name); }
    void SetName(const std::string& name);
    uint8_t GetAttributte(int attr, bool To7 = false);
    uint8_t GetAttributtesCalc();
    uint8_t GetAttributtesCalcTo7();
    std::string GenAttributeStr();
    SWSPlayerStruct_t GetRawData() { return data; } 
  private:
    SWSPlayerStruct data;
};

class SWSAPI SWSTeam
{
  public:
    SWSTeam();
    virtual ~SWSTeam() = default;
    bool Load(std::ifstream& ifs);
    bool Save(std::ofstream& ofs);
    std::string GetName() { return std::string(data.name); }
    void SetName(const std::string &name);
    uint8_t GetDivision() { return data.division; }
    void SetDivision(uint8_t div) { data.division = div; }
    std::shared_ptr<SWSPlayer> GetPlayer(int no);
    uint16_t GetAttributtesCalc();
    uint16_t GetAttributtesCalcTo7();
    SWSTeamStruct_t GetRawData() { return data; }
  private:
    SWSTeamStruct data;
    std::vector<std::shared_ptr<SWSPlayer>> m_Players;
};

struct SWSAPI SWSFileStr
{
  uint8_t teamscount;
  uint8_t dbteamno;
  void* swsfile;
};

typedef SWSFileStr SWSAPI SWSFileStr_t;

class SWSAPI SWSFile
{
  public:
    SWSFile();
    virtual ~SWSFile() = default;
    bool Load(const std::string& filename);
    bool Save(const std::string& filename);
    bool isOpened() { return m_Open; }
    bool isExternal() { return m_External; }
    void SetExternal(bool ext) { m_External = ext; }
    int GetTeamCount() { return m_Teamcount; }
    std::string& GetNationName() { return m_NationName; }
    void SetNationName(const std::string& nationname) { m_NationName = nationname; }
    std::string& GetFilename() { return m_Filename; }
    void SetFileName(const std::string& filename) { m_Filename = filename; }
    uint32_t GetSWSExeHex() { return m_SWSExeHex; }
    void SetSWSExeHex(uint32_t hex) { m_SWSExeHex = hex; }
    SWSDivisionTeams_t GetDivisionCount();
    std::shared_ptr<SWSTeam> GetTeam(int no);
    void FindPlayers(const std::string& name, std::vector< std::pair< std::pair< std::shared_ptr<SWSPlayer>, int>,std::shared_ptr<SWSTeam> >>& data);
  private:
    uint8_t m_Teamcount;
    SWSDivisionTeams m_DivisionCount;
    std::string m_Filename;
    std::string m_NationName;
    uint32_t m_SWSExeHex;
    bool m_Open;
    bool m_External;
    std::vector<std::shared_ptr<SWSTeam>> m_Teams;
};

class SWSAPI SWSDatabase
{
public:
  // path must finish with separator!
  SWSDatabase(const std::string& path);
  virtual ~SWSDatabase() = default;
  void SetDatabasePath(const std::string& path) { m_DBpath = path; }
  bool LoadAllDatabase();
  void SaveAllDatabase();
  int GetFilesCount() { return m_TeamFiles.size(); }
  std::shared_ptr<SWSFile> AddSWSFile(const std::string& filename);
  bool LoadSWSFile(int no);
  void FindPlayers(const std::string& name, std::vector< std::pair< std::pair< std::shared_ptr<SWSPlayer>, int>, std::shared_ptr<SWSTeam> >> & data);
  std::vector< std::pair< std::pair< std::shared_ptr<SWSPlayer>, int>, std::shared_ptr<SWSTeam> >> FindPlayerDuplicates();
  std::string& GetDatabasePath() { return m_DBpath; }
  std::shared_ptr<SWSFile> GetSWSFile(int no);
private:
  std::string m_DBpath;
  std::vector<std::shared_ptr<SWSFile>> m_TeamFiles;
};

}
extern "C"
{
  SWSAPI void* CreateDatabase(const char* path);
  SWSAPI void FreeDatabase(void* database);
  SWSAPI bool LoadAllDatabase(void* database);
  SWSAPI int GetDatabaseCount(void* database);
  SWSAPI void SaveAllDatabase(void* database);
  SWSAPI void FindDuplicates(void* database);
  SWSAPI bool AddFileToDatabase(void* database, const char* swsfile);
  SWSAPI bool GetSWSFileData(void* database, int fileno, SWOS::SWSFileStr_t* swsfile);
  SWSAPI int GetSWSTeamsCount(void* database, int fileno);
  SWSAPI bool GetSWSTeamData(void* database, int fileno, int teamno, SWOS::SWSTeamStruct_t swsteam);
}