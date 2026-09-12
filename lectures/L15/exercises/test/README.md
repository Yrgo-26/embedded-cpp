# L15 Testsvit

Enhetstester för allt som kursboken, §5.5 *Exercises*, övningsset 1-2, ber dig skriva, byggda på
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
| `language` | **alltid** | Vad §5.1 och §5.2 säger om funktionstemplates och type traits |
| `function_template` | `function_template/main.cpp` finns | `clear` och `toggle`, och programmets utskrift |

Övningsset 2 besvaras i text och har därför ingen binär. Innan du har börjat rapporteras setet som
`SKIP`, tillsammans med den fil sviten väntar på.

---

## Vad testerna kontrollerar

**Utskriften, exakt.** Testet jämför det programmet skriver ut med den förväntade utdatan i
övningen, tecken för tecken, och rapporterar den första rad som skiljer sig.

**Deklarationerna.** Båda templaten deklareras `constexpr` och `noexcept`, så testerna anropar dem vid
kompileringstid och frågar kompilatorn om `noexcept`. Ett template som enbart är korrekt vid körning
går inte att anropa i ett konstant uttryck, och kompilatorns meddelande säger varför.

**Breda register, som övningen inte använder.** `clear()` och `toggle()` testas på 32- och 64-bitars
register såväl som på det 8-bitars register övningen använder, eftersom `1U << 40` är odefinierat för
en 32-bitars `unsigned` och `static_cast<T>(1U) << 40` är det som gör rätt.

**Vad som inte får kompilera.** Övningen ber om en `static_assert()` som avvisar ett register av
icke-heltalstyp. `function_template_rejects_float_clear.cpp` och
`function_template_rejects_float_toggle.cpp` anropar `clear()` respektive `toggle()` på en `float`,
och sviten kontrollerar att de misslyckas *på grund av en statisk assertion*, snarare än av något
annat skäl.
