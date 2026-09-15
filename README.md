# Harmonies

## 1. What Is This Project?

Harmonies is an application based on the board game of the same name. It was
developed as a university project by a team of four students. The subject and
some constraints were given by the professor of the course. We used Git to work
together, and we also had to write three reports and make a presentation video.

I personally worked on this project again afterwards to clean it up and make it
more suitable for my GitHub profile.

This project helped me learn C++, OOP, Qt, algorithms, unit testing, Git, and
teamwork. I also proposed the first architecture of the application, with an
effort to separate responsibilities between the model, game flow, rules,
scoring, and UI layers.

## 2. My Contributions

During the university project, I worked mainly on the general architecture of
the application and on the full scoring system. I also implemented part of the
game rules and wrote unit tests for the files I developed.

I contributed to part of the Qt interface, especially where the UI had to be
connected with the game logic. I was also often the person reviewing pull
requests before they were merged, to check that the project still compiled and
that the changes were coherent with the rest of the code.

After the university project, I cleaned up the repository, improved the
Makefile, added GitHub Actions CI, and fixed some structural issues to make the
project easier to understand from the GitHub page.

## 3. Features

- Turn-based multiplayer gameplay
- Automatic score calculation
- Playable terminal version
- Playable Qt Widgets UI
- Implementation of the main game rules
- Board-game elements handled by the application: bag, boards, decks, cards,
  tokens, and player turns

## 4. Build And Run

Requirements:

- C++17 compiler
- `make`
- Qt Creator, for the graphical interface

```bash
make
```

This command compiles the console application.

```bash
make run
```

This command compiles and runs the terminal version.

```bash
make test
```

This command builds and runs all automated unit tests.

```bash
make clean
```

This command removes the generated object files and executables.

To run the graphical version, open the project with Qt Creator from the root
`HarmoniesQt.pro` file and start it normally.

## 5. Project Structure

- `include/model`: domain objects
- `include/core`: game flow
- `include/rules`: placement and end-game rules
- `include/scoring`: score calculation
- `tests`: automated tests
- `HarmoniesQt`: Qt Widgets UI

## 6. CI

I added the CI afterwards, although it would have been better to add it during
the project development. GitHub Actions builds the console application and runs
the tests on every push and pull request.

## 7. Status / Limitations

- The console build and tests are covered by CI.
- The Qt application is available, but it is not built by the CI.
- The UI was not the priority of the project. It is playable, but not perfectly
  user-friendly.
- The terminal version is playable, but not user-friendly.
- The game is missing some cards compared with the real board game.
- The original decks are not fully reproduced.
- The graphics were generated with AI.
- CMake would be a better long-term build system than the current Makefile.
- There is no Docker setup for now.
