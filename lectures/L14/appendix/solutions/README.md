# Lösningsförslag
Referensimplementation för övningarna i kursboken, §4.4 *Exercises*, övningsset 4,.

**OBS!** Försök att lösa övningarna själv innan du tittar på lösningsförslaget.

## Lösningsförslag
* [smart_factory](./smart_factory/include/app/logic/logic.hpp): Applikationslogik implementerad med
  smarta pekare och en
  [factory med smarta pekare](./smart_factory/include/driver/factory/interface.hpp).

Jämför med [raw_factory](../../../L13/appendix/solutions/raw_factory/include/app/logic/logic.hpp) i
L13: skillnaden mellan de två är hela poängen med lektionen.

## Att välja factory
Precis som i L13 används makrot `STUB` i `main.cpp` för att växla mellan ESP32-S3-factoryn och
stub-factoryn. Se [L13](../../../L13/appendix/solutions/README.md#att-välja-factory).

## Reflektion
**Vem raderar den seriella drivern nu, och när?**
* `std::unique_ptr`-medlemmen i `Logic` gör det, när `Logic`-objektet förstörs.
* Raderingen sker via det seriella interfacets virtuella destruktor, och exakt en gång.

**Varför kunde destruktorn i `Logic` tas bort helt?**
* Den enda uppgift den hade var att radera den råa pekaren. En `std::unique_ptr` gör det åt dig, så
  en explicit destruktor har ingenting att göra - och en destruktor som deklareras utan att behövas
  tar dessutom bort klassens implicita flyttoperationer.

**Vad skulle hända om anroparen kastade bort returvärdet från `serial()`?**
* Den temporära `std::unique_ptr` skulle förstöras omedelbart, och drivern med den: objektet vore
  skapat och raderat på samma rad. Det är därför metoden är märkt `[[nodiscard]]`.

---
