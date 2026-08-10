# LLM Log — Multiplayer Snake

## 1. Setup

| Field | Value |
|---|---|
| Model(s) | Gemini 2.5 Pro (Antigravity / Claude Sonnet 4.6 Thinking mode) |
| Tool / harness | Antigravity agentic coding assistant (in-IDE agent) |
| IDE / editor | VS Code with Antigravity |
| Did you paste this assignment document into it? | y — full assignment text pasted as the user prompt |

---

## 2. Session

### Prompt 1
> "Make it multiplayer" + full assignment text

**What I gave the LLM**: The agent read all 5 source files autonomously (`Snake.h`, `Snake.cpp`, `Food.h`, `Food.cpp`, `GameGrid.h`, `GameGrid.cpp`, `SnakeGame.cpp`). No manual file selection was needed — the agent listed the directory and read every file.

**What the agent did (attempt 1)**:

Created an implementation plan identifying 4 functions to change:
- `drawGameGrid(const Snake&, const Food&, int score)` → two-snake signature
- `showGameOver(int finalScore)` → two scores + loser id
- `randomFoodPosition(const vector<Point>&)` → two body vectors
- `main()` → two snakes, two scores, arrow key input for P1

Asked one clarifying question: since P1 already used W/A/S/D, which keys should P1 get? User confirmed: P1 → Arrow keys, P2 → W/A/S/D.

The agent then made all changes in one session:
1. `Food.h` — updated signature
2. `Food.cpp` — added second body check
3. `GameGrid.h` — updated both function signatures
4. `GameGrid.cpp` — rewrote `showGameOver` (two scores, loser announcement) and `drawGameGrid` (renders both snakes with distinct emoji, shows both scores)
5. `SnakeGame.cpp` — replaced `main()` with two-player loop

**Result**: Code compiled successfully on first attempt.

### Total prompts to working code: **1**

### What code was given: **Whole repository** (all 5 source files read autonomously)

### Which attempt finally worked: **Attempt 1** — no earlier failed attempts.

---

## 3. Notes

The agent identified two structural issues before writing code:

1. **Key conflict**: The original game used W/A/S/D for Player 1. The assignment says Player 2 uses W/A/S/D. Moving Player 1 to arrow keys was the only sensible resolution.

2. **`showGameOver`**: The original took a single `int finalScore` and had no concept of player identity. Adding "Player X lost!" required changing its signature to accept `score1`, `score2`, and `loser`.

Both were noted in the implementation plan before any code was written, consistent with the assignment's instruction not to act on restructuring findings.
