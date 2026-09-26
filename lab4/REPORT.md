# Lab 4 — Group A__

> Copy this file to `lab4/REPORT.md`, fill it in, then paste the finished text into your
> pull request description. Keep the six headings exactly as they are — they are the
> marking scheme, in order. Delete this quote block and every `___` when you are done.

| | |
|---|---|
| Repository | https://github.com/mshaikh19/Snake-Game-Project.git (your own snake game) |
| Base tag | `lab4-base` at commit `b3ecddd6c5668bb0c876fb6d364b3cf47a1e7d33` |
| Pull request | ___ |

---

## 1. Five rules — [5]

Written before opening the source. Behaviour, with an observable outcome.

| # | Rule |
|---|---|
| 1 | The snake is an ordered list of cells body[0] (head) … body[n-1] (tail). A move is legal only if the new head cell is empty; if that cell is already one of body[1..n-1], the snake has run into itself and the game ends. The blocking logic lives in the self-collision scan of Snake::isCollision() — it walks every segment after the head and returns true on the first coordinates match. A player observes this as the game-over screen. |
| 2 | The board is a rectangle of gridWidth × gridHeight. A head position with x < 0, x ≥ gridWidth, y < 0, or y ≥ gridHeight is off the playfield, so the snake dies. This is the boundary check at the top of Snake::isCollision() — the four comparisons against 0 and gridWidth/gridHeight. |
| 3 | There is a single place the score is mutated: when the head coincides with the fruit, the main loop executes score += 10. No other code path adds to score. So every fruit is worth exactly 10 (not “some amount”), and the displayed number (printf("%05d", score)) jumps by 10 each time. The snake also grows by one segment on that same frame, but the score change is precisely +10. |
| 4 | Food::randomFoodPosition() generates rand() % gridWidth, rand() % gridHeight, then checks the candidate against every segment of the snake body; it repeats until it finds a free cell. Therefore the invariant fruit.position ∉ snakeBody always holds after the call. Observable: the apple is always on an empty cell. The one thing you cannot assert is which cell it lands on, because rand() is non-deterministic — that is the testing blocker for this rule. |
| 5 | In the game loop, kbhit() tests whether a key is waiting, and getch() reads it. W/A/S/D are forwarded to Snake::setDirection(), which updates the heading (and silently drops a 180° reversal, e.g. D→A). X/x breaks out of the loop (quit). Observable outcomes: the snake turns to the pressed key, or the game exits on X. The blocker: input is read live from the console via getch() inside the loop — there is no seam to feed fake keys, so the rule cannot be driven by a test without changing the source. |

If you could not state one of your own game's rules without going to look, say which and
why. It costs no marks.

Rule 3 — "Eating a fruit increases the score by exactly 10 points."

Without the source, a player only sees the score jump on screen; the exact constant (+10) and the guarantee that no other code path ever mutates the score are only certain from reading main(), where score is an internal local (SnakeGame.cpp:132) with its single increment score += 10 at SnakeGame.cpp:164.

---

## 2. What you could test, and what stopped you — [10]

No source changes in this part. Every `file:line` below is a line in `lab4-base`.

| # | Rule | Test written? | Blocking dependency (`file:line` + what it is) |
|---|---|---|---|
| 1 | Snake dies when its head enters its own body | Yes | -- |
| 2 | Snake dies when its head leaves the board | Yes | -- |
| 3 | Eating a fruit increases the score by exactly 10 | No | SnakeGame.cpp:132 — score is a local int inside main(); only mutated score += 10 at SnakeGame.cpp:164 inside the loop that blocks on getch() at SnakeGame.cpp:142 |
| 4 | Fruit never appears on a cell occupied by the snake | Yes | -- |
| 5 | Player steers with W/A/S/D; X quits	 | No | SnakeGame.cpp:142 — getch() reads live console input inside the game loop (SnakeGame.cpp:135–173), kbhit() at :141; no way to inject keys; X-quit break at SnakeGame.cpp:143 |

> **Rules testable without modifying the source: 3 / 5**

"It needs user input" is not a blocking dependency. `main.cpp:214 — getch() called inside
the game loop` is.

Two lines of defence are genuinely untestable because they are inside main()'s getch/sleep loop with no injection point — exactly the getch/sleep blockers the lab expects. The seam in Part D goes on one of them.

---

## 3. Coverage, and what it missed — [6]

| | |
|---|---|
| Line coverage | 90.5 % (57 / 63 lines executed: Snake.cpp 37/43 [86.1%], Food.cpp 20/20 [100%]) |
| Branch coverage | 91.8 % executed (67 / 73 branches), 68.5 % taken (50 / 73 branches) |
| Command used | `g++ --coverage -O0 -g Snake.cpp Food.cpp tests/test_rules.cpp -o tests && ./tests && gcov -b tests-Snake.gcno tests-Food.gcno` |

**One rule that is executed by the suite but not verified by it:**

| | |
|---|---|
| Rule | Rule 5: Player steers with W/A/S/D |
| Line that runs | `Snake.cpp:38` (`currentDirection = snakeDirection;`) inside `Snake::setDirection()` |
| The assertion that is missing | `assert(snake.getDirection() == 'W');` |

---

## 4. The seam — [10]

| | |
|---|---|
| Rule made testable | Rule 5: Player steers with W/A/S/D; X quits |
| Commit 1 (seam) | `29049c5` — Add InputSource interface and processGameInput seam function |
| Commit 2 (test) | `2a6d416` — Add unit tests for Rule 5 steering and quit using StubInputSource |
| Seam kind | object |
| Enabling point | `processGameInput(InputSource& inputSource, char& direction)` in `InputSource.h`, called in `SnakeGame.cpp:139` |
| What production code gave up | Direct I/O coupling and tight encapsulation of console input. Production code surrendered its hardcoded call to global `conio.h` functions (`_kbhit()` / `_getch()`), delegating input queries to an injected polymorphic `InputSource&` interface reference. |

---

## 5. The double — [4]

| | |
|---|---|
| What you passed through the seam | stub |
| The method under test | `processGameInput(InputSource& inputSource, char& direction)` |

The collaborator `InputSource` was asked a question (`hasInput()` / `getInput()`) to query for available keyboard input. Because methods returning values provide inputs to the caller rather than performing a side-effect, the test double supplies canned responses acting as a **stub** (simulating pre-configured user keypresses without real hardware I/O).

---

## 6. Two smells in your own tests — [5]

| | Smell | `file:line` | One-line fix |
|---|---|---|---|
| 1 | Assertion Roulette | `tests/test_rules.cpp:15` | Add descriptive failure message: `assert(!snake.isCollision() && "Snake should not collide on initial valid move");` |
| 2 | Conditional / Non-deterministic Test Loop | `tests/test_rules.cpp:44` | Replace random `for` loop with explicit, deterministic grid occupation assertions or a fixed RNG seed |
