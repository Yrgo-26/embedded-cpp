# L13 Testsvit

Enhetstester för allt som kursboken, §4.4 *Exercises*, övningsset 1-3, ber dig skriva, byggda på
ramverket [QAcademy Test](https://github.com/qrtech-academy/test-framework), som ligger utcheckat
som submodulen `libs/test`. Kör `git submodule update --init` en gång om den katalogen är tom.

```bash
make                    # Bygg och kör sviten mot din kod i ../
make SOLUTIONS=1        # Samma tester, mot ../../appendix/solutions
make clean              # Ta bort testbinärerna.
```

`make test` i repots rot kör denna svit och samtliga andra lektioners.

> **Du ska inte skriva några tester i denna kurs.** Testsviten är given och färdig: du skriver din
> lösning på övningarna och kör `make test` för att se om den gör vad övningen ber om. Det här
> dokumentet beskriver vad sviten kontrollerar, så att ett testresultat går att tolka - det är inte
> en uppgift.
>
> Att själv skriva tester kommer i kursen **hårdvarunära testning**. Ordningen är avsiktlig: här får
> du se vad en testsvit är bra för, innan du skriver din första.

---

## Vad som körs, och när

| Binär | Byggs när | Testar |
|---|---|---|
| `language` | **alltid** | Vad §4.1 säger om `new`, `delete` och virtuella destruktorer |
| `exercise1` | de tre filerna i `raw_factory/include/driver/serial` finns | Det seriella interfacet, stubben och ESP32-S3-drivern |
| `exercise2` | de tre filerna i `raw_factory/include/driver/factory` finns | Factory-interfacet och de två factories, med råa pekare |
| `exercise3` | `raw_factory/include/app/logic/logic.hpp` finns | Logikklassen, och att den äger sin driver korrekt |

Ett set vars filer ännu inte finns rapporteras som `SKIP`, tillsammans med den sökväg sviten väntar
på. En fil som skrivits under fel namn blir därmed synlig i stället för tyst otestad.

---

## Vad testerna kontrollerar

**Deklarationerna, som typer.** En metods exakta signatur, `const` och `noexcept` inkluderat, är en
del av dess typ, så testerna jämför typer för pekare till medlemsfunktioner: `write()` måste vara
exakt `void (Interface::*)(std::uint8_t) noexcept`. En avvikelse fäller ett namngivet test. Raderade
kopierings- och flyttoperationer, `final` och virtuella destruktorer kontrolleras med type traits,
och `explicit` på ESP32-S3-driverns konstruktor genom att kontrollera att
`Esp32s3 serial = {17U, 18U};` inte kompilerar.

**Utskriften, exakt.** `driver::serial::Esp32s3::write()` ska skriva ut
`Transmitting byte 0xFF via TX pin 17!`, precis som i övningen. En andra byte och ett annat
pin-nummer säkerställer att ingetdera är hårdkodat, och att det är sändningspinnen som skrivs ut.

**Ägandeskap, genom räkning.** För att testa `Logic` ger testerna den en egen factory, som spelar in
vad den ombads skapa och skapar drivrutiner som räknar sin egen destruktion. En `Logic` som ber om
sin driver mer än en gång, med fel pin-nummer, aldrig raderar den, eller raderar den två gånger,
faller därför med ett antal. Att konstruera och förstöra `Logic`-objektet sker i en barnprocess,
eftersom en driver som raderas två gånger oftast kraschar: testet faller då med signalen och en fråga
(*is its driver deleted twice?*), och testerna efter det körs ändå.

**`run()`, från utsidan.** `run()` returnerar aldrig, så testerna kan inte anropa den och vänta.
[`run_probe.hpp`](./run_probe.hpp) kör den i en barnprocess med en seriell driver som rapporterar
varje anrop genom en pipe, tittar på i 450 ms och dödar den därefter. Det är tillräckligt länge för
att se vad Övning 3.1 d) ber om: bytesen 0, 1, 2, ... i ordning, en läsning efter varje skrivning,
fyra eller fem skrivningar snarare än tusentals (fördröjningen på 100 ms), och en utskriven rad per
mottagen byte och ingen annars. Vad `run()` skriver ut jämförs inte, eftersom övningen inte säger
hur det ska se ut.

**Vad som inte testas.** Att `isInitialized()` och `serial()` är `[[nodiscard]]`, och att `read()`
inte är det: GCC varnar inte för ett bortkastat resultat från ett virtuellt anrop gjort via ett
interface, med attributet eller utan, så inget test kan skilja dem åt. `main.cpp` kompileras mot dina
headerfiler men körs aldrig, eftersom det aldrig avslutas; kör det själv.
