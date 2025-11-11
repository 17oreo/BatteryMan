# 🔋 BatteryMan

BatteryMan is a small third-person game built in **Unreal Engine 5**, originally inspired by a UE4 Battery Collector tutorial on YouTube.  
The project demonstrates core Unreal gameplay concepts — **movement, jumping, collectibles, UI, and basic game logic** — all recreated from scratch in **C++** and **Blueprints**.

---

## 🎮 Gameplay Overview

Play as **BatteryMan**, a robot whose energy drains over time.  
Collect **battery pickups** scattered throughout the map to recharge and survive longer!

### ⚙️ Core Features
- 🧍 **Fully custom C++ character class**
  - Handles movement, jumping, and camera control in C++
- ⚡ **Collectible system**
  - Detects overlaps with the player and destroys the battery on pickup  
  - Simple recharge mechanic that increases battery life  
  - Batteries spawn randomly every 2–5 seconds at random X/Y locations (set using `UPROPERTY(EditAnywhere)`)
- 🎥 **Third-person camera**
  - Built with a spring arm and follow camera system
- 🕹️ **Enhanced Input ready**
  - Compatible with UE5’s modern input mapping context system
- 🔋 **Battery UI**
  - Widget Blueprint displays the player’s current energy level
- ☠️ **Game End**
  - When the battery runs out, BatteryMan ragdolls  
  - The game restarts automatically after 3 seconds

---

## 💡 Purpose

This project was developed as a **learning tool** to expand my knowledge of Unreal Engine 5’s C++ systems, input handling, collision detection, and UI integration.

---

### 🛠️ Built With
- Unreal Engine 5
- C++ & Blueprints
- Visual Studio 2022
- Widget Blueprints (UI)

---
