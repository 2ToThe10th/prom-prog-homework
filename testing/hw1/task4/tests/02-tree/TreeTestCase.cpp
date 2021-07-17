//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"

TEST_F(TreeTestCase, NotExists) {
  EXPECT_THROW(GetTree((boost::filesystem::temp_directory_path() / boost::filesystem::unique_path()).string(), true),
               std::invalid_argument);
}

TEST_F(TreeTestCase, NotADirectory) {
  auto tmp_file = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
  boost::filesystem::ofstream(tmp_file.string());
  EXPECT_THROW(GetTree(tmp_file.string(), true),
               std::invalid_argument);
}

TEST_F(TreeTestCase, EmptyDirectory) {
  auto tmp_dir = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
  boost::filesystem::create_directories(tmp_dir.string());
  auto node = GetTree(tmp_dir.string(), true);
  EXPECT_EQ(node.name, tmp_dir.filename().string());
  EXPECT_TRUE(node.is_dir);
  EXPECT_TRUE(node.children.empty());
}

TEST_F(TreeTestCase, DirectoryWithDirAndFile) {
  auto root_dir = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
  boost::filesystem::create_directories(root_dir.string());
  auto dir = root_dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir.string());
  auto file = root_dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(file.string());
  auto node = GetTree(root_dir.string(), false);
  EXPECT_EQ(node.name, root_dir.filename().string());
  EXPECT_TRUE(node.is_dir);
  EXPECT_EQ(node.children.size(), 2);
  auto found_dir = node.children[0];
  auto found_file = node.children[1];
  if (found_file.is_dir) {
    std::swap(found_file, found_dir);
  }
  EXPECT_EQ(found_dir.name, dir.filename().string());
  EXPECT_TRUE(found_dir.is_dir);
  EXPECT_TRUE(found_dir.children.empty());
  EXPECT_EQ(found_file.name, file.filename().string());
  EXPECT_FALSE(found_file.is_dir);
  EXPECT_TRUE(found_file.children.empty());

  FileNode expected{root_dir.filename().string(), true, {{dir.filename().string(), true, {}}}};
  EXPECT_FALSE(node == expected);
}

TEST_F(TreeTestCase, DirectoryWithDirAndFileOnlyDir) {
  auto root_dir = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
  boost::filesystem::create_directories(root_dir.string());
  auto dir = root_dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir.string());
  auto file = root_dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(file.string());
  auto node = GetTree(root_dir.string(), true);
  FileNode expected{root_dir.filename().string(), true, {{dir.filename().string(), true, {}}}};
  EXPECT_EQ(node, expected);
}

void SortNodeByName(FileNode &node) {
  std::sort(node.children.begin(), node.children.end(), [](FileNode &a, FileNode &b) {
    return a.name < b.name;
  });
  for (auto &children: node.children) {
    SortNodeByName(children);
  }
}

TEST_F(TreeTestCase, BigDir) {
  auto root_dir = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
  boost::filesystem::create_directories(root_dir.string());
  auto dir = root_dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir.string());
  auto file = root_dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(file.string());
  auto dir_file2 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file2.string());
  auto dir_file3 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file3.string());
  auto dir_dir1 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir1.string());
  auto dir_dir2 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir2.string());
  auto dir_file1 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file1.string());
  auto dir_file4 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file4.string());
  auto dir_dir3 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir3.string());
  auto dir_dir4 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir4.string());
  auto dir_file7 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file7.string());
  auto dir_file8 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file8.string());
  auto dir_dir5 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir5.string());
  auto dir_dir6 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir6.string());
  auto dir_file5 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file5.string());
  auto dir_file6 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file6.string());
  auto node = GetTree(root_dir.string(), false);
  SortNodeByName(node);
  FileNode expected{root_dir.filename().string(), true,
                    {{dir.filename().string(), true,
                      {
                          {dir_dir1.filename().string(), true, {}},
                          {dir_dir2.filename().string(), true, {}},
                          {dir_dir3.filename().string(), true, {}},
                          {dir_dir4.filename().string(), true, {}},
                          {dir_dir5.filename().string(), true, {}},
                          {dir_dir6.filename().string(), true, {}},
                          {dir_file1.filename().string(), false, {}},
                          {dir_file2.filename().string(), false, {}},
                          {dir_file3.filename().string(), false, {}},
                          {dir_file4.filename().string(), false, {}},
                          {dir_file5.filename().string(), false, {}},
                          {dir_file6.filename().string(), false, {}},
                          {dir_file7.filename().string(), false, {}},
                          {dir_file8.filename().string(), false, {}},
                      }
                     },
                     {file.filename().string(), false, {}}}};
  SortNodeByName(expected);
  EXPECT_EQ(node, expected);
  FilterEmptyNodes(node, root_dir.string());
  EXPECT_TRUE(boost::filesystem::exists(root_dir.string()));
  EXPECT_TRUE(boost::filesystem::exists(dir.string()));
  EXPECT_FALSE(boost::filesystem::exists(dir_dir1.string()));
}

TEST_F(TreeTestCase, BigDirDirsOnly) {
  auto root_dir = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
  boost::filesystem::create_directories(root_dir.string());
  auto dir = root_dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir.string());
  auto file = root_dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(file.string());
  auto dir_file2 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file2.string());
  auto dir_file3 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file3.string());
  auto dir_dir1 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir1.string());
  auto dir_dir2 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir2.string());
  auto dir_file1 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file1.string());
  auto dir_file4 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file4.string());
  auto dir_dir3 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir3.string());
  auto dir_dir4 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir4.string());
  auto dir_file7 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file7.string());
  auto dir_file8 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file8.string());
  auto dir_dir5 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir5.string());
  auto dir_dir6 = dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir_dir6.string());
  auto dir_file5 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file5.string());
  auto dir_file6 = dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(dir_file6.string());
  auto node = GetTree(root_dir.string(), true);
  SortNodeByName(node);
  FileNode expected{root_dir.filename().string(), true,
                    {{dir.filename().string(), true,
                      {
                          {dir_dir1.filename().string(), true, {}},
                          {dir_dir2.filename().string(), true, {}},
                          {dir_dir3.filename().string(), true, {}},
                          {dir_dir4.filename().string(), true, {}},
                          {dir_dir5.filename().string(), true, {}},
                          {dir_dir6.filename().string(), true, {}},
                      }
                     }}};
  SortNodeByName(expected);
  EXPECT_EQ(node, expected);
  FilterEmptyNodes(node, root_dir.string());
  EXPECT_TRUE(boost::filesystem::exists(root_dir.string()));
  EXPECT_TRUE(boost::filesystem::exists(dir.string()));
  EXPECT_FALSE(boost::filesystem::exists(dir_dir1.string()));
}

TEST_F(TreeTestCase, FilterEmptyNodes) {
  auto root_dir = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
  boost::filesystem::create_directories(root_dir.string());
  auto dir = root_dir / boost::filesystem::unique_path();
  boost::filesystem::create_directories(dir.string());
  auto file = root_dir / boost::filesystem::unique_path();
  boost::filesystem::ofstream(file.string());
  auto node = GetTree(root_dir.string(), false);
  FilterEmptyNodes(node, root_dir.string());
  EXPECT_FALSE(boost::filesystem::exists(dir));
  EXPECT_TRUE(boost::filesystem::exists(file));
}

TEST_F(TreeTestCase, CheckNotEqual) {
  FileNode xxx_dir{"xxx", true, {}};
  FileNode xxx_file{"xxx", false, {}};
  FileNode yyy_dir{"yyy", true, {}};
  EXPECT_FALSE(xxx_dir == xxx_file);
  EXPECT_FALSE(xxx_dir == yyy_dir);
}