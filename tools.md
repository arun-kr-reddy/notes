- [git](#git)
- [create new repo:](#create-new-repo)
- [repo checkout:](#repo-checkout)
- [add \& commit:](#add--commit)
- [push changes:](#push-changes)
- [branching:](#branching)
- [update \& merge:](#update--merge)
- [diff:](#diff)
- [tag:](#tag)
- [log:](#log)
- [misc:](#misc)
- [mermaid UML](#mermaid-uml)
- [powershell](#powershell)
- [ffmpeg](#ffmpeg)
- [vlc](#vlc)
- [youtube](#youtube)

# links  <!-- omit from toc -->
- [git guide](http://rogerdudler.github.io/git-guide/)
- [git parable](httsps://www.youtube.com/watch?v=jm7QsI-nNjk)
- [clang format](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- [cmake](https://codevion.github.io/#!cpp/cmake.md)
- [makefile](https://makefiletutorial.com/)
- [mermaid UML](https://jojozhuang.github.io/tutorial/mermaid-cheat-sheet/)

# git
- ![](./media/tools/git_workflow.png)
- ```sh
  # create new repo:
  git init                               # create a new git repo

  # repo checkout:
  git clone /path/to/repo                # copy of a local repo
  git clone username@host:/path/to/repo  # from a remote server

  # add & commit:
  git add   <filename>                   # working ⟶ index
  git commit -m "<message>"              # index ⟶ head

  # push changes:
  git push origin <branch>               # head ⟶ remote
  git remote add origin <server>         # connect local repo to a remote server

  # branching:
  git checkout <branch>                  # checkout/switch-to a branch
  git checkout -b <branch>               # create a branch & switch to it
  git branch -d <branch>                 # delete a branch

  # update & merge:
  git fetch <name>                       # fetch changes (but doesn't change anything in workspace)
  git merge <name>/<branch>              # integrate changes from someone else
  git pull                               # detach & merge in a single command

  # diff:
  git diff                               # working vs index
  git diff --staged                      # index vs commit
  git diff HEAD                          # working vs head
  git diff <from> <to>                   # commit vs commit

  # tag:
  git tag -l                             # list current tags
  git tag <tag> <commit>                 # create a tag pointing to a commit

  # log:
  git log                                # look at repo history
  git log --author=<user>                # only commits from certain author
  git log --pretty=oneline               # compressed log
  git log --name-status                  # only see files that have changed

  # misc:
  git status                             # changes in working directory & index
  git checkout -- <filename>             # replace working directory file changes with one in HEAD
  git fetch origin && git reset --hard origin/master  # drop all local changes & commits
  ```

## cmake
- **cmake:** *CMakeLists.txt* used to generate standard build files (makefiles or MSVC project)  
  ```cmake
  cmake_minimum_required(VERSION 3.10)
  set(CMAKE_CXX_STANDARD 11)

  set(SOURCES main.cpp)             # set variable
  include_directories(./include)    # header path
  project(test_project)             # project name
  add_subdirectory(subdir)          # include subdir cmakelists
  add_executable(main_exe SOURCES)  # executable target
  ```
- **library:**
  ```cmake
  add_library(mylib STATIC lib.cpp)            # create lib
  find_library(PTHREAD_LIB pthread)            # find system lib
  find_library(CUSTOM_LIB myLib PATHS <path>)  # find custom lib at path
  target_link_libraries(main_exe ${PTHREAD_LIB} ${CUSTOM_LIB})  # include lib
  ```

# mermaid UML
- **flowchart:**
  - **direction:** `TB` , `BT`, `RL`, `LR`
  - **shape:** rect `[ ]`, rounded rect `( )`, circle `(( ))`, rhombus `{ }`  
    ![](./media/tools/flowchart_symbols.png)
  - **connection:** link `---`, arrow `-->`, dotted arrow `-.->`
  ```sh
  graph LR
    a((start))
    b[func1]
    c[func2]
    d{cond}
    e((end))

    a --> b
    b --> d
    d -- yes --> c
    d -- no --> e
    c --> e
  ```
  ```mermaid
  graph LR
    a((start))
    b[func1]
    c[func2]
    d{cond}
    e((end))

    a --> b
    b --> d
    d -- yes --> c
    d -- no --> e
    c --> e
  ```
- **sequence diagram:** participants in order of declaration
  - **connection:** line `->`, dotted line `-->`, arrow `->>`, dotted arrow `-->>`  
    activation period by appending `+` & `-` to message
  - **notes:** `Note [direction] [participants]: [message]`  
    direction can be `right of`, `left of`, `over`  
    for `over` multiple comma-separated participants can be added  
  - **loops:** `loop <title>\n  statements...\n  end`
  ```sh
  sequenceDiagram
    participant thread1
    participant thread2
    participant thread3

    thread1 ->>+ thread2: frame_start

    loop busy_wait
        thread2 -->> thread3: reg_read
        thread3 -->> thread2: reg_val
    end

    thread2 ->>+ thread3: frame
    thread3 ->>- thread2: output

    Note over thread1, thread2: some comment
    thread2 ->>- thread1: frame_done
  ```
  ```mermaid
  sequenceDiagram
    participant thread1
    participant thread2
    participant thread3

    thread1 ->>+ thread2: frame_start

    loop busy_wait
        thread2 -->> thread3: reg_read
        thread3 -->> thread2: reg_val
    end

    thread2 ->>+ thread3: frame
    thread3 ->>- thread2: output

    Note over thread1, thread2: some comment
    thread2 ->>- thread1: frame_done
  ```

# powershell
- **replace string in all filenames:**
  ```sh
  get-childitem *.mp4 | foreach { rename-item $_ $_.Name.Replace("Lecture ","") }
  ```

# ffmpeg
- **mkv to mp4:**
  ```sh
  for %f in (*.mkv) do ffmpeg -i "%f" -codec copy "%f.mp4"
  ```
- **concatenate multiple files:**
  ```sh
  ffmpeg -f concat -i merge.txt -c copy merged.mp4

  # merge.txt
  file '1.mp4'
  file '2.mp4'
  file '3.mp4'
  ```
- **change resolution:**
  ```sh
  ffmpeg -i input_720p.mp4 -s 640x360 -c:a copy output.mp4
  ffmpeg.exe -i input.mp4 -filter:v scale=-2:360 -c:a copy output.mp4
  ```

# vlc
- **filename as title:** `tools` ⟶ `preferences` ⟶ `all` ⟶ `input/codecs` ⟶ `all` ⟶ `change title..` ⟶ `$U`
- **always on top:** `view` ⟶ `always on Top`
- **default minimal view:** `tools` ⟶ `preferences` ⟶ `all` ⟶ `interface` ⟶ `main interfaces` ⟶ `qt` ⟶ `start in minimal view`
- **always continue playback:** `tools` ⟶ `preferences` ⟶ `interface` ⟶ `continue Playback` ⟶ `always`

# youtube
- **channel playlist:** replace second char `C` with `U` in channel ID (from its about section) and append it to `https://www.youtube.com/playlist?list=`