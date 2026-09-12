# L14 Testsvit

Enhetstester för allt som kursboken, §4.4 *Exercises*, övningsset 4, ber dig skriva, byggda på
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
| `language` | **alltid** | Vad §4.2 säger om `std::unique_ptr` |
| `exercise1` | `smart_factory/include/driver/factory/interface.hpp` finns | Factory-interfacet, de två factories och logikklassen, med smarta pekare |

`exercise1` slås på fil för fil: den börjar med det nya factory-interfacet och plockar upp factories
och logikklassen i takt med att du uppdaterar dem. Tills dess rapporteras setet som `SKIP`,
tillsammans med den sökväg sviten väntar på.

---

## Vad testerna kontrollerar

**Returtypen, som typ.** `serial()` måste returnera exakt
`std::unique_ptr<driver::serial::Interface>`, fortfarande ta två pin-nummer och fortfarande vara
`noexcept`. Testerna jämför typen för pekaren till medlemsfunktionen, så en factory som returnerar
`std::unique_ptr<driver::serial::Esp32s3>` fäller ett namngivet test.

**Att det är rätt driver som skapas.** ESP32-S3-factoryns `serial()` ska returnera en pekare som
faktiskt håller en `driver::serial::Esp32s3`, skapad med de pin-nummer som skickades in, och
stub-factoryns ska returnera en `driver::serial::Stub` och ignorera pin-numren. Testerna kontrollerar
båda, genom att använda den returnerade drivern.

**Ägandeskap, genom räkning.** `Logic` ges en egen factory som skapar drivrutiner som räknar sin egen
destruktion. Drivern ska skapas exakt en gång, med rätt pin-nummer, och förstöras exakt en gång när
`Logic`-objektet förstörs - utan någon destruktor i `Logic`.

**`run()`, från utsidan.** Precis som i L13 körs `run()` i en barnprocess via
[`run_probe.hpp`](./run_probe.hpp) och bevakas i 450 ms, för att se vad Övning 1.3 d) ber om.

**Vad som inte testas.** Att `serial()` är `[[nodiscard]]`: GCC varnar inte för ett bortkastat
resultat från ett virtuellt anrop gjort via ett interface. `main.cpp` kompileras mot dina headerfiler
men körs aldrig, eftersom det aldrig avslutas; kör det själv.
