# AP-Backup

## Image orientation
- All images, if having direction, are toward right by default. If you want to add your image, please ensure that it's toward right.

## Type enum of user-defined QGraphicsItem
(`i` indicates `Type = UserType + 1`)
- [1, 99]: `Area` and its derived class
- [101, 199]: `Monster`'s derived class
- [201, 299]: `Character`'s derived class
- [1001, ]: Particles(kinds of visual effects)

## Add Custom buff
If you want to add your custom buff, please follow steps below
- First, add it to enum class `Buff`.
- If it is a buff that can be set on a character by hand (i.e., your would see an option button at upper right corner):
  - Add it to the list in `BuffUtil::characterBuffs()`;
  - Give it an icon in BuffUtil::buffToIcon() (remember to add icon path to `img_rsc.qrc` and path string to BuffUtil)
- If it is a de-buff, add it to `BuffUtil::isDeBuff()`.
- Add its effect where you want.
  - e.g. If effect is decrease damage, add your code to `Entity::getDamage()`, or anywhere else you like.
- If it works through attack action, I recommend you to make it by ActionAttack system:
  - e.g. `Buff::CAUSE_CORROSION` add `Buff::CORROSION` to target; it adds `Buff::CORROSION` to ActionAttack in `Entity::attack()` first, and target will get it in `Entity::attacked()`.
