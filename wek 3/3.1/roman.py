class Roman:
    roman_map = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}

    def __init__(self, value):
        if isinstance(value, str):
            self.roman = value.upper()
            self.decimal = self.from_roman(self.roman)
        elif isinstance(value, int):
            self.decimal = value
            self.roman = self.to_roman(self.decimal)
        else:
            raise ValueError("Недопустимый тип данных. Используйте str (римское число) или int (десятичное число).")

    def __str__(self):
        return self.roman

    def __repr__(self):
        return f"Roman('{self.roman}')"

    def __add__(self, other):
        if isinstance(other, Roman):
            return Roman(self.decimal + other.decimal)
        elif isinstance(other, int):
            return Roman(self.decimal + other)
        else:
            raise TypeError("Неподдерживаемый тип операнда для +")

    def __sub__(self, other):
        if isinstance(other, Roman):
            return Roman(self.decimal - other.decimal)
        elif isinstance(other, int):
            return Roman(self.decimal - other)
        else:
            raise TypeError("Неподдерживаемый тип операнда для -")

    def __mul__(self, other):
        if isinstance(other, Roman):
            return Roman(self.decimal * other.decimal)
        elif isinstance(other, int):
            return Roman(self.decimal * other)
        else:
            raise TypeError("Неподдерживаемый тип операнда для *")

    def __truediv__(self, other):
        if isinstance(other, Roman):
            if other.decimal == 0:
                raise ZeroDivisionError("Деление на ноль!")
            return Roman(self.decimal // other.decimal)
        elif isinstance(other, int):
            if other == 0:
                raise ZeroDivisionError("Деление на ноль!")
            return Roman(self.decimal // other)
        else:
            raise TypeError("Неподдерживаемый тип операнда для /")

    @staticmethod
    def to_roman(num):
        if not 0 < num < 4000:
            raise ValueError("Число должно быть в диапазоне от 1 до 3999")

        roman_map = {1: 'I', 4: 'IV', 5: 'V', 9: 'IX', 10: 'X', 40: 'XL', 50: 'L', 90: 'XC', 100: 'C', 400: 'CD', 500: 'D', 900: 'CM', 1000: 'M'}
        i = 12
        result = ""

        while num != 0:
            if list(roman_map.keys())[i] <= num:
                result += list(roman_map.values())[i]
                num -= list(roman_map.keys())[i]
            else:
                i -= 1
        return result

    @staticmethod
    def from_roman(roman_num):
        roman_map = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
        result = 0
        i = 0
        while i < len(roman_num):
            if i + 1 < len(roman_num) and roman_map[roman_num[i]] < roman_map[roman_num[i + 1]]:
                result += roman_map[roman_num[i + 1]] - roman_map[roman_num[i]]
                i += 2
            else:
                result += roman_map[roman_num[i]]
                i += 1
        return result