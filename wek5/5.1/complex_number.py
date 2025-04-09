class Complex:
    def __init__(self, real: float = 0, imag: float = 0): #Инициализация комплексного числа
        
        self.real = real
        self.imag = imag
    
    def __str__(self) -> str: #Строковое представление комплексного числа
        
        sign = '+' if self.imag >= 0 else '-'
        return f"{self.real} {sign} {abs(self.imag)}i"
    
    def to_dict(self) -> dict: #Преобразует комплексное число в словарь для сериализации
        return {'real': self.real, 'imag': self.imag}
    
    @classmethod
    def from_dict(cls, data: dict) -> 'Complex': #Создает комплексное число из словаря
        return cls(data['real'], data['imag'])