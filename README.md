# Shift Brite Animator

Some wrapper classes to make working with the ShiftBrite shield more enjoyable.

## Setup

```
// First, set NUM_LEDS to how many leds you have in your string.
#define NUM_LEDS 10

// Then create an Array full of LEDs
LED lights[NUM_LEDS];

// Create a shield:
ShiftBriteShield shield (lights, NUM_LEDS);

// And now create an animator
ShiftBriteAnimator animator(&shield);
```

It should be feasible to do this in one step: ```ShiftBriteAnimator animator(NUM_LEDS);```, but this is how I feel when writing C++:
![dog](http://i.imgur.com/3MLiwS9.jpg?1 "Really")

## Usage

Now animations on your LED string are super simple:
```
animator.fill();
animator.clear();
animator.chase();
```
Check the method definitions in ```ShiftBriteAnimator.cpp``` for options available to pass.

## Pull Requests
I'd love pull requests, especially with new / improved animations and hitting me with some C++ knowledge.

## Shoutouts
Some of the code in the ShiftBriteShield class came from the examples on Macetech's site. http://macetech.com/blog/node/54
