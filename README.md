# CS 330: Final Project


## Requirement 1 (Single/Multi-User Online Game)

0. Each team can have up to **three** people
1. The goal is to create either
   * a single (and/or multi-)user game, or 
   * a simulation of the routing mechanism
2. In terms of the single-user game, it could be [hangman](https://en.wikipedia.org/wiki/Hangman_(game)), [guess the number](https://www.goobix.com/games/guess-the-number/)), or something fun
3. The multi-user game (two+ players) could be [tic-tac-toe](https://playtictactoe.org/), [bingo](https://en.wikipedia.org/wiki/Bingo_(American_version)), or others you like
4. The game server will accept connections from multiple users and allow them to run single-user game (and/or pair two users to play the multi-user game)
5. You can use any language (C, C++, C#, Python, Java, Go, etc.)
6. The core component should involve socket programming
7. Every team has to commit their weekly progress, including, but not limited to code, status/meeting report, discussions, weekly plan, etc.
8. Final Presentation on 5/3 (and possibly also 4/28 if we have too many teams)
9. In terms of the routing mechanism, you will create software routers which accepts the connections from multiple clients and route the messages to the appropriate clients based on the forwarding/routing tables.
   9.1. The client will send a message which carries the IP addresses and port numbers of the source/destination.
   9.2. You'll implement the trie structure to carry out the longest-prefix matching in routing
   9.3. There will be multiple clients and routers, each client is connected to a fixed router

## What to submit

  * Individual contributions will be evaluated through commits - **DO NOT** use a single account to commit your work (other members will get 0 pts)
  * Whenever the team meets, record the discussions in the meeting in a document
  * Document your work in PDF, Word, or other formats

* **Week 1 (15%)**: team forming, decide the project, plan for the project, roles/actions for each team member, etc.
  * Outline your plan in GitHub Issues/Milestones/Web/etc.
* **Week 2 (15%)**: prototyping, skeleton code, etc.
  * Record/update the status of the issues/milestones/etc.
* **Week 3 (15%)**: coding, testing, debugging
  * Record/update the status of the issues/milestones/etc.
* **Week 4 (15%)**: coding, fine tuning, testing, delivering
  * Record/update the status of the issues/milestones/etc.
* Presentation and peer evaluation: 40%

## Note

1. Your work will be evaluated **weekly**.
2. Only commit once as the final submission will result in **0 points to the whole team (no exception/excuse will be accepted)**
3. Be creative.