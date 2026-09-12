# L16 Testsvit

Enhetstester för allt som kursboken, §5.5 *Exercises*, övningsset 3, ber dig skriva, byggda på
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
| `language` | **alltid** | Vad §5.3 säger om klasstemplates och specialisering |
| `class_template` | `class_template/include/driver/timer/timer.hpp` finns | `Timer`-templaten och dess STM32-specialisering, och programmet när `source/main.cpp` finns |

Innan du har börjat rapporteras setet som `SKIP`, tillsammans med den sökväg sviten väntar på.

---

## Vad testerna kontrollerar

**Att det är två skilda typer.** `Timer<Type::Stub>` och `Timer<Type::Stm32>` ska vara olika typer,
genererade ur en primär template och en full specialisering, och `Timer<>` ska vara stub-varianten
tack vare default-argumentet. Testerna frågar kompilatorn med type traits.

**Samma publika interface i båda.** Specialiseringen ska erbjuda samma metoder med samma signaturer
som den primära templaten - `const`, `noexcept` och `[[nodiscard]]` inkluderat. Ett test som anropar
samma metoder på båda kompilerar bara om så är fallet.

**Utskriften, exakt.** Konstruktorernas, destruktorernas och metodernas utskrifter jämförs tecken för
tecken, inklusive den ogiltiga timeouten 0 och de olika texterna för stub- respektive
STM32-varianten. Programmets utskrift jämförs på samma sätt med den förväntade utdatan i övningen.

**De gränsfall som specifikationen namnger.** En timer som skapas med timeouten 0 är inte initierad,
och `start()` samt `toggle()` ska lämna den stoppad. En timer som är igång löper ut på exakt sitt
timeout:te tick, och `hasTimedOut()` återställer räknaren.
