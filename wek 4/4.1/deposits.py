class TermDeposit:
    def __init__(self, amount, months, rate):
        self.amount = amount
        self.months = months
        self.rate = rate
    
    def calculate_profit(self):
        # Простые проценты: P = S * (r/100) * (t/12)
        return self.amount * self.rate / 100 * self.months / 12

class BonusDeposit:
    def __init__(self, amount, months, rate, bonus_threshold, bonus_percent):
        self.amount = amount
        self.months = months
        self.rate = rate
        self.bonus_threshold = bonus_threshold
        self.bonus_percent = bonus_percent
    
    def calculate_profit(self):
        base_profit = self.amount * self.rate / 100 * self.months / 12
        if self.amount >= self.bonus_threshold:
            bonus = base_profit * self.bonus_percent / 100
            return base_profit + bonus
        return base_profit

class CapitalizationDeposit:
    def __init__(self, amount, months, rate):
        self.amount = amount
        self.months = months
        self.rate = rate
    
    def calculate_profit(self):
        # Сложные проценты с ежемесячной капитализацией
        monthly_rate = self.rate / 100 / 12
        total = self.amount * (1 + monthly_rate) ** self.months
        return total - self.amount