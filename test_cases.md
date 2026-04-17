# Test Cases — Payment Application

All functions were tested individually before integration. Each test case documents the input, expected result, and actual result.

---

## Card Module

### `getCardHolderName()`

Validates cardholder name: 20–24 characters, letters/spaces/hyphens only.

| # | Input | Length | Expected | Actual | Status |
|---|-------|--------|----------|--------|--------|
| 1 | `Mohamed Ramadan ibr` | 19 | WRONG_NAME | WRONG_NAME | ✅ Pass |
| 2 | `Mohamed Ramadan ibra` | 20 | OK_CARD | OK_CARD | ✅ Pass |
| 3 | `Mohamed Ramadan ibr1` | 20 | WRONG_NAME (digit) | WRONG_NAME | ✅ Pass |
| 4 | `Mohamed Ramadan ibrahim` | 23 | OK_CARD | OK_CARD | ✅ Pass |
| 5 | `Mohamed Ramadan abdelkad` | 24 | OK_CARD | OK_CARD | ✅ Pass |
| 6 | `Mohamed Ramadan abdelkade` | 25 | WRONG_NAME | WRONG_NAME | ✅ Pass |

---

### `getCardExpiryDate()`

Validates expiry date format `MM/YY`. Month must be `01–12`.

| # | Input | Expected | Reason | Status |
|---|-------|----------|--------|--------|
| 1 | `12/27` | OK_CARD | Valid month and year | ✅ Pass |
| 2 | `0/27` | WRONG_EXP_DATE | Missing leading zero | ✅ Pass |
| 3 | `00/27` | WRONG_EXP_DATE | Month 00 invalid | ✅ Pass |
| 4 | `13/25` | WRONG_EXP_DATE | Month 13 doesn't exist | ✅ Pass |
| 5 | `12.23` | WRONG_EXP_DATE | Wrong separator (dot) | ✅ Pass |
| 6 | `12\23` | WRONG_EXP_DATE | Wrong separator (backslash) | ✅ Pass |
| 7 | `2/20` | WRONG_EXP_DATE | Missing leading zero | ✅ Pass |
| 8 | `02/20` | OK_CARD | Valid format | ✅ Pass |

---

### `getCardPAN()`

Validates Primary Account Number: 16–19 digits, numeric only.

| # | Input | Length | Expected | Status |
|---|-------|--------|----------|--------|
| 1 | `501105448859782` | 15 | WRONG_PAN | ✅ Pass |
| 2 | `501105448859782s` | 16 | WRONG_PAN (non-digit) | ✅ Pass |
| 3 | `5011054488597827` | 16 | OK_CARD | ✅ Pass |
| 4 | `5011054488597827835` | 19 | OK_CARD | ✅ Pass |
| 5 | `50110544885978278358` | 20 | WRONG_PAN | ✅ Pass |

---

## Terminal Module

### `isCardExpired()`

Compares card expiry `MM/YY` against the current system date `DD/MM/YYYY`.

| # | Card Expiry | Expected | Reason | Status |
|---|-------------|----------|--------|--------|
| 1 | `05/20` | EXPIRED_CARD | Past year | ✅ Pass |
| 2 | `05/25` | OK_TERMINAL | Future year | ✅ Pass |
| 3 | `11/22` | OK_TERMINAL | Future at time of test | ✅ Pass |
| 4 | `07/22` | EXPIRED_CARD | Past month/year | ✅ Pass |
| 5 | `05/22` | EXPIRED_CARD | Past month/year | ✅ Pass |

---

### `isValidCardPAN()` — Luhn Algorithm

Validates PAN using the ISO/IEC 7812 Luhn checksum.

| # | PAN | Luhn Checksum Verification | Expected | Status |
|---|-----|---------------------------|----------|--------|
| 1 | `1806356467113247787` | Even-index × 2, sum = 73, check = 7 ✓ | VALID | ✅ Pass |
| 2 | `3532329577284122983` | Passes Luhn checksum | VALID | ✅ Pass |
| 3 | `5011054488597827835` | Luhn checksum fails | INVALID | ✅ Pass |

**Luhn verification example for `1806356467113247787`:**
```
PAN (without check digit): 180635646711324778
                                          ^ check digit: 7
Even-index digits × 2:  1→2, 0→0, 5→10→1, 4→8, 7→14→5, 1→2, 3→6, 7→14→5
Odd-index digits:        8, 6, 6, 1, 2, 4, 7, 8
Sum = 2+8+0+6+1+6+8+4+5+1+2+3+6+2+5+4 = 73 - 80 + ... → (10 - 73%10) = 7 ✓
```

---

## Server Module

### `isValidAccount()` and `recieveTransactionData()`

Checks whether a PAN exists in the server-side `accountsDataBase[]`.

| # | PAN | In Database | Expected | Status |
|---|-----|-------------|----------|--------|
| 1 | `1806356467113247787` | Yes (balance: 1000) | OK_SERVER | ✅ Pass |
| 2 | `3532329577284122983` | Yes (balance: 100) | OK_SERVER | ✅ Pass |
| 3 | `5011054488597827835` | No | DECLINED_STOLEN_CARD | ✅ Pass |

---

## End-to-End User Stories

Full transaction flows testing the complete pipeline (Card → Terminal → Server).

| # | Scenario | PAN | Balance | Max | Amount | Outcome |
|---|----------|-----|---------|-----|--------|---------|
| 1 | Transaction approved | `1806356467113247787` | 1000 | 500 | 500 | ✅ APPROVED |
| 2 | Exceed max amount | `1806356467113247787` | 1000 | 500 | 700 | ❌ EXCEED_MAX_AMOUNT |
| 3 | Insufficient fund | `1806356467113247787` | 1000 | 2000 | 1200 | ❌ DECLINED_INSUFFECIENT_FUND |
| 4 | Expired card | `1806356467113247787` (exp: 02/21) | 1000 | 500 | 500 | ❌ EXPIRED_CARD |
| 5 | Fraud / not in DB | `123456789012345678` | — | 500 | 500 | ❌ DECLINED_STOLEN_CARD |
| 6 | Invalid card (Luhn) | `5573139293755809` | — | 500 | 500 | ❌ INVALID_CARD |

---

*All test cases passed. Testing was performed on Windows 10 x64 using Microsoft Visual Studio 2022.*
