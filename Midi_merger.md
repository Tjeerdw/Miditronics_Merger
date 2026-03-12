Miditronics Organ System — Context for MIDI Merger (this board and firmware)

What it is

A MIDI-controlled pipe organ system built around ESP32 microcontrollers. Each PCB is an independent module
that either reads physical keys/buttons and sends MIDI, or receives MIDI and drives solenoid/relay outputs to actuate
organ pipes and stops.

Module Types (each PCB runs one of these)

Noten Up to 64 note keys → MIDI NoteOn/Off, or MIDI → 64 solenoid outputs       │
Registers Up to 64 register switches → MIDI CC 80/81, or MIDI → 64 register outputs │

MIDI Protocol Used
-Notes: Standard NoteOn/NoteOff, velocity always 127, configurable start note and MIDI channel (1–6)
-Registers: CC 80 (value = register number) = register ON, CC 81 (value) = register OFF on channel 8 and 9
-Panic/Reset: NoteOff with pitch 127 = all notes off; CC 81 with value 127 = all registers off 
-Each module listens on its own configurable MIDI channel (notes and registers can be on separate channels in split
modes)

How the Merger Fits In
The system has multiple input modules (keyboards, pedalboard, register panels) each sending MIDI on their own channel.
The 7-input / 1-output MIDI merger combines all these streams into a single MIDI bus that feeds the output modules
(which drive the actual organ pipes and stops). Each output module filters by its configured MIDI channel, so the
merger must pass all channels through correctly and apply routing logic.

Hardware: Teensy 4.1. 7 serial MIDI inputs (Serial1-7) + 1 USB MIDI input. Serial8 is the single merged output.
All routing logic lives in KoppelUnit (miditools.h / miditools.cpp).

Routing Logic — Koppels (organ couplers)
The merger implements organ coupler logic. Channels map to manuals/pedal:
  Ch1=Manual I, Ch2=Manual II, Ch3=Manual III, Ch4=Manual IV, Ch5=Manual V, Ch6=Pedal

Manual Koppels: A koppelList (24 entries) defines which source channel routes to which destination channel.
  Example: koppel "I+II" routes Manual I notes also to Manual II output channel.
  Koppels are enabled/disabled at runtime via CC80 (on) / CC81 (off) on MIDI channel 10, where data2 is the koppel ID value.

Note Memory (notesMem): A per-channel, per-note bitmask (notesMem[channel][note], 32-bit) tracks which koppels
  have activated each note. This prevents double-triggering when multiple koppels activate the same note,
  and ensures a note-off is only sent when all sources have released the note.

Hot-enable/disable: When a koppel is enabled while notes are held, those notes are immediately played on the
  destination channel. When disabled, notes that were held by that koppel are turned off.

Octave Couplings (16'): Some koppel entries have a transpose value of -12 semitones (one octave down).
  These implement 16' sub-octave couplings, e.g. "I+II 16'" plays Manual I notes one octave lower on Manual II.

Register passthrough: CC messages on channels 8 and 9 are passed through unchanged (register on/off).

Status of Transposing Feature
The last two commits (2025-03-31, "added 3 octave couplings in KL" and "untested implementation of tranposing")
added octave coupling entries and transpose logic to koppelNoteOn/Off. This code is UNTESTED and BUGGY:
  - note+transpose can go negative for low notes, causing array out-of-bounds on notesMem
  - the koppel-disable NoteOff loop double-applies the transpose offset
The last known working commit is 6ac9ff4 (2023-12-29). The transposing feature should be fixed before use.