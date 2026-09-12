# Lösningsförslag
Referensimplementation för övningarna i kursboken, §4.4 *Exercises*, övningsset 1-3,.

**OBS!** Försök att lösa övningarna själv innan du tittar på lösningsförslaget.

## Lösningsförslag
* [raw_factory](./raw_factory/include/app/logic/logic.hpp): Applikationslogik implementerad med råa
  pekare och en [factory med råa pekare](./raw_factory/include/driver/factory/interface.hpp).

Lösningsförslaget till övningsset 4, med smarta pekare, finns i
[L14](../../../L14/appendix/solutions/README.md).

## Att välja factory
Lösningsförslaget använder makrot `STUB` i `main.cpp` för att växla mellan ESP32-S3-factoryn och
stub-factoryn. Detta är enbart för bekvämlighet och krävdes inte av övningen.

Exempelapplikationen kan byggas med antingen ESP32-S3-drivrutinerna eller stub-drivrutinerna.

Som standard används stub-drivrutinerna, eftersom makrot `STUB` är definierat i `main.cpp`:

```cpp
#define STUB
```

För att i stället använda ESP32-S3-drivrutinerna, kommentera bort eller ta bort definitionen:

```cpp
// #define STUB
```

Applikationslogiken (`app::logic::Logic`) behöver inte ändras. Enbart den valda factoryn ändras.

## Reflektion
**Vilken kod i `Logic` behövde ändras när du bytte från ESP32-S3-factoryn till stub-factoryn?**
* Ingen kod i `Logic` behövde ändras.
* Logikklassen beror enbart på det abstrakta factory-interfacet och det abstrakta seriella
  interfacet, inte på de konkreta ESP32-S3- eller stub-implementationerna.
* Det innebär att applikationslogiken kan använda antingen riktiga hårdvarudrivrutiner eller
  stub-drivrutiner utan att ändras.

**Vilken kod i `main()` behövde ändras?**
* Enbart den konkreta factory-typ som skapas i `main()` behövde ändras.
* I stället för att skapa en `driver::factory::Esp32s3` skapar `main()` en `driver::factory::Stub`.
* Resten av koden kan lämnas orörd, eftersom båda factories implementerar samma factory-interface.

---
