# Detailed Usage Scenario

1. **Character Creation**
   1. Prompt: "Enter your character's name" → User inputs a string (e.g., "Aria").
   2. Prompt class choice:
      - Input 1 → Warrior
      - Input 2 → Mage
      *Validation*: non-integer or out-of-range reprompts until valid.
   3. Prompt stats distribution: 10 points total between Strength and Intelligence.
      - Input two integers summing to 10, both ≥ 0.
      *Validation*: reprompt on invalid sum or format.
   4. Weapon selection:
      - 1: Sword (damage 18, dur 25)
      - 2: Staff (damage 3, dur 5 + custom effect)
   5. Armor selection:
      - 1: Light Armor (+5 agility, low defense)
      - 2: Medium Armor
      - 3: Heavy Armor
   6. Skill selection (choose one or none):
      - Heal, Increase Inventory, Monk Training, EasyBlock,
      - Warriors may also learn SpellCast.
   7. Item selection (choose one or none):
      - Fireball Scroll, Small Mana Potion, Repair Kit, None.

2. **Difficulty Selection**
   - Prompt: "Choose difficulty: 1-Easy, 2-Medium, 3-Hard"
   - Validation: ensure integer 1–3.

3. **Combat Loop** (each turn up to AP=initial_ap=10):
   1. Display status: HP/MaxHP, Mana/MaxMana, AP/MaxAP, equipped gear, inventory list.
   2. Display options:
      1) Attack → Choose Melee or SpellCast (if available)
      2) Block → Reduces next incoming damage; Warriors gain buff on success.
      3) Inventory → List items 1..n → select to use or dispose.
      4) Investigate → Randomly adds new item → AP–=invest_cost.
      5) Concentrate → Mana +=10, AP +=1 → AP–=conc_cost.
      6) Heal (if learned) → HP +=healAmount → AP–=heal_cost.
      7) Display Status → no AP cost.
      0) End Turn → exit options loop.
   3. Subtract AP and Mana per action (costs as per Constants.h).

4. **Enemy Turn**
   - Follows similar AP-based loop with AI decisions:
     - Ultra Attack, Heal, Restore Mana, Buff, Item Use, SpellCast, MeleeAttack, Block.
   - Ends when AP < minimum action cost.

5. **Combat End**
   - Condition: player or enemy HP ≤ 0.
   - Outcome: "Victory" or "Defeat" message.