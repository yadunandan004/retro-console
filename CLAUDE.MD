PROJECT: Chip-8 Emulator in C++ - Learning-Focused Implementation

=== CONTEXT ===
I'm a senior software engineer (distributed systems background) learning modern C++ through hands-on projects. I want to build a Chip-8 emulator as a fun weekend project that teaches low-level programming concepts.

This is a LEARNING project, not a race to completion. I want to understand:
- How emulators work at a fundamental level
- CPU instruction fetch-decode-execute cycle
- Memory management and addressing
- Bit manipulation and opcodes
- Graphics rendering to framebuffer
- Binary file I/O

=== REQUIREMENTS ===

DEVELOPMENT ENVIRONMENT:
- macOS (M1/M2/Intel - specify which you have)
- C++20 features encouraged where they make code cleaner
- SDL2 for graphics/input (install via: brew install sdl2)
- CMake for build system
- Modern tooling (clang++, gdb/lldb for debugging)

PROJECT STRUCTURE:
chip8-emulator/
├── CMakeLists.txt
├── src/
│   ├── chip8.h         # Chip8 class declaration
│   ├── chip8.cpp       # Core emulator logic
│   ├── main.cpp        # SDL2 integration + main loop
│   └── platform.h      # SDL2 wrapper (optional)
├── roms/               # Chip-8 ROM files
└── README.md

IMPLEMENTATION APPROACH:
I want to build this INCREMENTALLY with your guidance:

Phase 1: Minimal Working System
- Basic Chip8 class (memory, registers, PC)
- Load ROM file into memory
- Implement 3-5 essential opcodes to see SOMETHING work
- Simple SDL2 window showing display array
- Goal: Run a trivial program and see output

Phase 2: Full Instruction Set
- Implement remaining opcodes methodically
- Test each opcode group before moving to next
- Add proper error handling
- Goal: Run simple games (Pong works)

Phase 3: Complete Features
- Keyboard input mapping
- Sound/beep timer
- Proper timing (60Hz cycle rate)
- Goal: Run all classic Chip-8 games

=== TEACHING STYLE ===

IMPORTANT - I want to LEARN, so please:

✅ DO:
- Explain WHY we're doing things, not just WHAT
- Show me the Chip-8 specification relevant to each part
- Point out interesting bit manipulation tricks
- Explain opcodes as we implement them
- Help me understand the CPU cycle
- Suggest debugging approaches when things break
- Encourage me to implement things myself after explanation

❌ DON'T:
- Dump complete working code without explanation
- Skip over important concepts
- Give me "just use this" solutions
- Implement everything at once
- Use magic numbers without explaining them
- Rush through the instruction set
- Write logic/function implementations on my behalf - explain the concept and let ME write the code. Static data (like lookup tables, constants) is fine, but logic is mine to implement.

TEACHING APPROACH:
For each opcode group, I want:
1. Explanation of what it does conceptually
2. Show me the bit pattern/format
3. Guide me through implementation logic
4. Let me attempt the code first, then review
5. Test it before moving on

=== TECHNICAL PREFERENCES ===

CODE STYLE:
- Clear variable names (not x, y everywhere - use descriptive names)
- Comments explaining opcodes (e.g., // 0x6XNN: Set VX to NN)
- Separate concerns (CPU logic vs rendering vs input)
- Modern C++ practices (smart pointers if appropriate, RAII)

DEBUGGING:
- Help me add debug output to trace execution
- Show me how to print CPU state
- Teach me how to verify opcodes are working
- Include assertions for invalid states

=== STARTING POINT ===

Please help me with:

1. PROJECT SETUP:
    - Create CMakeLists.txt with SDL2 linking
    - Show me how to verify SDL2 is installed correctly
    - Basic project structure

2. CHIP-8 ARCHITECTURE OVERVIEW:
    - Explain memory layout (0x000-0xFFF)
    - Explain registers (V0-VF, I, PC, SP)
    - Explain display (64x32 monochrome)
    - Explain timers (delay, sound)

3. MINIMAL SKELETON:
    - Chip8 class with essential members
    - Load ROM function
    - Placeholder for fetch-decode-execute
    - SDL2 window creation

4. FIRST OPCODES:
   Help me implement these first (explained one at a time):
    - 0x00E0: Clear screen
    - 0x6XNN: Set register VX to NN
    - 0x7XNN: Add NN to register VX
    - 0xDXYN: Draw sprite (most important!)

Let's start with #1 (project setup) and work incrementally from there.

QUESTION: Before we start coding, can you:
- Confirm SDL2 installation works
- Explain at a high level how the fetch-decode-execute cycle will work
- Show me what a simple Chip-8 program looks like in hex so I understand what we're interpreting

Remember: I want to UNDERSTAND this, not just copy code. Teach me!
```

---

## **Why This Instruction Works:**

**1. Sets Learning Expectations:**
- Claude Code knows you want explanations, not just code
- Emphasizes incremental learning
- Requests teaching approach

**2. Provides Context:**
- Your background (so it knows your level)
- Your goals (learning, not just completion)
- Technical preferences

**3. Clear Structure:**
- Phases you can work through
- Specific starting point
- Room for iteration

**4. Prevents Common Mistakes:**
- No code dumps without explanation
- No rushing through content
- Focus on understanding

**5. Technical Details:**
- Mac environment
- SDL2 setup
- Modern C++ preferences
- Debugging approach

---

## **What to Expect:**

**Claude Code should respond with:**
1. Verification of SDL2 installation
2. High-level explanation of Chip-8 architecture
3. Project structure setup
4. CMakeLists.txt
5. Basic skeleton code with explanations
6. First opcode to implement (with teaching)

**Then you iterate:**
- Implement what it teaches
- Ask questions when stuck
- Request next opcode explanation
- Build incrementally

---

## **Pro Tips:**

**1. When Claude Code gives you code:**
```
YOU: "Wait, explain this line: opcode & 0x0FFF
What's the bit manipulation doing here?"
```

**2. Before implementing new opcodes:**
```
YOU: "Before showing me the code for 0x8XY4,
explain what ADD with carry means and why
we need the carry flag"
```

**3. When debugging:**
```
YOU: "My sprite drawing isn't working. Help me
add debug output to see what's happening.
What should I print to trace the issue?"
```

**4. After each phase:**
```
YOU: "I finished Phase 1. Before moving to Phase 2,
what should I understand about what I just built?
What are the key concepts?"