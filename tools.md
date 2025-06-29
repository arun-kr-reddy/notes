# tools
- [markdown](#markdown)
- [mermaid](#mermaid)
  - [flowchart](#flowchart)
  - [sequence diagram](#sequence-diagram)
  - [gantt diagram](#gantt-diagram)
  - [class diagram](#class-diagram)
  - [git graph](#git-graph)
  - [quadrant chart](#quadrant-chart)
  - [X-Y chart](#x-y-chart)
- [tech tips](#tech-tips)
  - [errors](#errors)
- [system reset](#system-reset)
  - [factory reset](#factory-reset)
  - [windows](#windows)

## todo <!-- omit from toc -->
- [python scripting](https://www.youtube.com/watch?v=1DtlzSDdk4s)
- [linux commands](https://www.youtube.com/watch?v=gd7BXuUQ91w)
- [cmake](https://youtu.be/7YcbaupsY8I)
- [GDB](https://www.youtube.com/watch?v=bWH-nL7v5F4)
- [git](https://www.youtube.com/watch?v=jm7QsI-nNjk)

## markdown
- [supported code block languages](https://github.com/jincheng9/markdown_supported_languages)
## [mermaid](https://mermaid.js.org/intro/)

### flowchart
- all mentioned nodes in subgraph grouped together
- **node shapes:**
  | shape         | symbol        | use          |
  | ------------- | ------------- | ------------ |
  | oval          | `id1((text))` | start/end    |
  | parallelogram | `id1[/text/]` | input/output |
  | rectangle     | `id1[text]`   | process node |
  | diamond       | `id1{text}`   | decision     |
- ```text
  graph LR
    a((start))
    b[func1]
    c[func2]
    d[/input/]
    e{cond}
    f((end))

    a --> b
    b --> e
    c --> f
    e -- no --> f

    subgraph process
    e -- yes --> c
    d -. copy .-> c
    end
  ```
  ```mermaid
  graph LR
    a((start))
    b[func1]
    c[func2]
    d[/input/]
    e{cond}
    f((end))

    a --> b
    b --> e
    c --> f
    e -- no --> f

    subgraph subgroup
    e -- yes --> c
    d -. copy .-> c
    end
  ```

### sequence diagram
- participants rendered in order of declaration
- activation period by appending `+` & `-` to connection
- `autonumber` to auto-generate sequence numbers
- ```text
  sequenceDiagram
    title example sequence diagram
    autonumber
    participant t1 as thread1
    participant t2 as thread2
    participant t3 as thread3

    t1 ->>+ t2: frame_start

    loop busy_wait
      t2 -->> t3: reg_read
      t3 -->> t2: reg_val
    end

    alt if_flag
      t2 -->> t2: post_process
    end

    par core1
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    and core2
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    end

    note over t1, t2: some comment
    t2 ->>- t1: frame_done
  ```
  ```mermaid
  sequenceDiagram
    title example sequence diagram
    autonumber
    participant t1 as thread1
    participant t2 as thread2
    participant t3 as thread3

    t1 ->>+ t2: frame_start

    loop busy_wait
      t2 -->> t3: reg_read
      t3 -->> t2: reg_val
    end

    alt if_flag
      t2 -->> t2: post_process
    end

    par core1
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    and core2
    t2 ->>+ t3: frame
    t3 ->>- t2: output
    end

    note over t1, t2: some comment
    t2 ->>- t1: frame_done
  ```

### gantt diagram
- ```text
  gantt
    dateFormat YYYY-MM-DD
    title example gantt diagram
    excludes weekends

    section sectionA
      start : milestone, start, 2025-01-01, 0d
      task1 : done, t1, after start, 2d
      task2 : active, t2, after t1, 3d
      task3 : t3, after t2, 5d

    section sectionB
      task5 : crit, t4, after t3, 2d
      task6 : t5, after t4, 3d
      end : milestone, after t5, 0d
  ```
  ```mermaid
  gantt
    dateFormat YYYY-MM-DD
    title example gantt diagram
    excludes weekends

    section sectionA
      start : milestone, start, 2025-01-01, 0d
      task1 : done, t1, after start, 2d
      task2 : active, t2, after t1, 3d
      task3 : t3, after t2, 5d

    section sectionB
      task5 : crit, t4, after t3, 2d
      task6 : t5, after t4, 3d
      end : milestone, after t5, 0d
  ```

### class diagram
- **relations:**
  | symbol     | use               |
  | ---------- | ----------------- |
  | `<\|--`    | inheritance       |
  | `*--`      | composition       |
  | `o--`      | aggregation       |
  | `-->`      | association       |
  | `---`      | link              |
  | `..>`      | dependency        |
  | `..>`      | realization       |
  | `<\|--\|>` | two-way relations |
- ```text
  classDiagram
    namespace BaseShapes {
      class Shapes{
        <<interface>>
        +area(Shapes) int
      }
      class Square{
          %% variables
          +int length
          %% method with arguments & return value
          +area(Square) int
      }
      class Rectangle{
          +int length
          +int breadth
          +area(Rectangle) int
      }
      class Circle{
          +int radius
          +area(Circle) float
          +circumference(Circle) float
      }
      class Random{
        +List~int~ points
        +area(List~int~ points) int
      }
    }

    Shapes <|-- Circle
    Shapes <|-- Rectangle
    Rectangle <|-- Square : parent
    Shapes <|-- Random

    note for Circle "defined in /shapes/circle.hpp"
  ```
  ```mermaid
  classDiagram
    namespace BaseShapes {
      class Shapes{
        <<interface>>
        +area(Shapes) int
      }
      class Square{
          %% variables
          +int length
          %% method with arguments & return value
          +area(Square) int
      }
      class Rectangle{
          +int length
          +int breadth
          +area(Rectangle) int
      }
      class Circle{
          +int radius
          +area(Circle) float
          +circumference(Circle) float
      }
      class Random{
        +List~int~ points
        +area(List~int~ points) int
      }
    }

    Shapes <|-- Circle
    Shapes <|-- Rectangle
    Rectangle <|-- Square : parent
    Shapes <|-- Random

    note for Circle "defined in /shapes/circle.hpp"
  ```

### git graph
- ```text
  gitGraph LR:
    title example git graph
    commit id: "commit1"
    commit id: "commit2"
    branch develop
    checkout develop
    commit id: "commit3"
    commit id: "reverse commit3" type: REVERSE
    commit id: "commit4"
    checkout main
    merge develop
    commit id: "commit5" type: HIGHLIGHT tag:"v1.0"
    commit id: "commit6"
  ```
  ```mermaid
  gitGraph LR:
    title example git graph
    commit id: "commit1"
    commit id: "commit2"
    branch develop
    checkout develop
    commit id: "commit3"
    commit id: "reverse commit3" type: REVERSE
    commit id: "commit4"
    checkout main
    merge develop
    commit id: "commit5" type: HIGHLIGHT tag:"v1.0"
    commit id: "commit6"
  ```

### quadrant chart
- without points quadrant titles in the centre
- ```text
  quadrantChart
    title example quadrant chart
    x-axis low talent --> high talent
    y-axis low agency --> high agency
    quadrant-1 game changers
    quadrant-2 go-getters
    quadrant-3 cogs in wheel
    quadrant-4 frustated geniuses

    candidate_1: [0.3, 0.6]
    candidate_2: [0.45, 0.23]
    candidate_3: [0.57, 0.69]
    candidate_4: [0.78, 0.34]
    candidate_5: [0.40, 0.34]
    candidate_6: [0.35, 0.78]
  ```
  ```mermaid
  quadrantChart
    title example quadrant chart
    x-axis low talent --> high talent
    y-axis low agency --> high agency
    quadrant-1 game changers
    quadrant-2 go-getters
    quadrant-3 cogs in wheel
    quadrant-4 frustated geniuses

    candidate_1: [0.3, 0.6]
    candidate_2: [0.45, 0.23]
    candidate_3: [0.57, 0.69]
    candidate_4: [0.78, 0.34]
    candidate_5: [0.40, 0.34]
    candidate_6: [0.35, 0.78]
  ```

### X-Y chart
- ```text
  xychart-beta
    title "example X-Y chart"
    x-axis [jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec]
    y-axis "savings (in ₹)" 0 --> 10000000
    bar [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9500000]
    line [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9500000]
  ```
  ```mermaid
  xychart-beta
    title "example X-Y chart"
    x-axis [jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec]
    y-axis "savings (in ₹)" 0 --> 10000000
    bar [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9500000]
    line [10000, 50000, 200000, 1000000, 1500000, 2500000, 3000000, 3500000, 5000000, 6000000, 8000000, 9500000]
  ```

## tech tips

### errors
- **google drive download limit exceeded:**
  - right click ⟶ organize ⟶ add shorcut ⟶ new folder ⟶ add
  - download that folder

## system reset

### factory reset
- **oppo TWS:**
  - forget from all devices
  - remove it from case
  - touch both buds for 20s
- **realme neckband:**
  - tap center button 5 times
  - hold center button for 10s

### windows
- **remove bing results from search:**
  - `reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Search" /v BingSearchEnabled /t REG_DWORD /d 0 /f`
- **open video downloader `binaries missing`:**
  - open `C:\Users\arun\AppData\Local\Programs\youtube-dl-gui\resources\app.asar.unpacked\binaries`
  - paste [yt-dlp.exe](https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp.exe)
- **windows 11 old context menu:**
  - `reg add "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f /ve`