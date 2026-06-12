# Password Strength Checker (C)

**My first ever programming project.**

I wrote a password strength checker in C back when I was first learning to program at
university. In true beginner fashion, my first ever `git push` silently failed — and this
repo sat here for years containing nothing but a licence file. I only noticed when I
cleaned up my GitHub recently, so I rebuilt it and finally gave the repo its code.

It checks a password the way I later learned real systems think about them:

- length (8+, and 12+ for full marks)
- mix of lowercase, uppercase, numbers and symbols
- whether it appears on a list of the world's most common passwords
  (instant fail — length and symbols can't save `qwerty`)

…then scores it out of 6 and prints tips for fixing the weak spots.

## Build & run

```
gcc password_checker.c -o password_checker
./password_checker
```

```
Password: qwerty

--- Password Report ---
Length        : 6
Strength      : VERY WEAK (0/6)

!! This is one of the most common passwords in the world.
```

## What it taught me

Functions, loops, structs, string handling — and that you should always check your
`git push` actually worked. Fitting that my first project was about password security,
given where I'm heading: I'm now CompTIA Security+ certified and building toward a
career in cybersecurity.
