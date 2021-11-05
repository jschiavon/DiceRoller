The format for the rollstring is as follows (not mandatory options are between square brackets):

### [Rx] NdD [+M]

where:
* **R** : Number of _repetitions_. If present, repeat R times the roll
* **N** : _Number_ of dice to roll
* **D** : Number of _sides_ of the dice to roll
* **M** : _Modifier_. If present, add M to the result of rolling

*Example*: 3x 2d20 +2 roll for 3 times 2 20-sided dice and adds 2 to each result.

The available options are:
* _Reroll 1s_: allows to reroll (once) each result of 1 that appears in the roll
* _Boon and Bane_: allows to add any number of boon (resp. bane) dices. One rolls as much d6 as there are boons (banes) and then add (subtract) the highest of these to the main roll.
* _Advantage and Disadvantage_: if advantage (disadvantage) is selected, rolls twice the dice and keep the highest (lowest) result.

If **Expectation** is pressed instead of **Roll!**, the application computes the expected value of the single roll (so the parameter **R** if present is ignored), but keeps track of all the options.
