from enum import Enum

class Shift(Enum):
    DAY = 1
    NIGHT = 2

class Date:
    def __init__(self, year: int, month: int, day: int):
        if year < 0:
            raise ValueError("Year must be positive")
        if month < 1 or month > 12:
            raise ValueError("Month must be between 1 and 12")
        days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31][month - 1]
        is_leap_year = year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)
        if day < 1 or day > days_in_month and not (month == 2 and day == 29 and is_leap_year):
            raise ValueError("Day must be between 1 and " + str(days_in_month + (1 if month == 2 and is_leap_year else 0)))

        self.year = year
        self.month = month
        self.day = day
    
    def __str__(self):
        return str(self.year) + "-" + str(self.month) + "-" + str(self.day)
    
    def __lt__(self, other):
        if not isinstance(other, Date):
            raise TypeError("Cannot compare Date with " + str(type(other)))     
        if self.year < other.year:
            return True
        if self.year > other.year:
            return False
        if self.month < other.month:
            return True
        if self.month > other.month:
            return False
        if self.day < other.day:
            return True
        return False


class Cook:
    def __init__(self, name: str, hire_date: str):
        self.name = name
        self.hire_date: str = hire_date

class FastFoodCook(Cook):
    def __init__(self, name: str, hire_date: str, shift: Shift):
        super().__init__(name, hire_date)
        self.shift = shift
        
def main():
    valid = False
    while not valid:
        prompt = input("Enter a number of fast food cooks: ")
        try:
            num_cooks = int(prompt)
            valid = True
        except ValueError:
            print("Invalid input.")
    cooks: list[FastFoodCook] = []

    i = 0
    while i < num_cooks:
        name = input("Enter name of cook: ")
        hire_date = input("Enter hire date of cook: ") # Format: YYYY-MM-DD
        shift = input("Enter shift of cook (1 for day, 2 for night): ")
        try:
            shift = Shift(int(shift))
            hire_date = hire_date.split("-")
            hire_date = Date(int(hire_date[0]), int(hire_date[1]), int(hire_date[2])) 
        except ValueError:
            print("Invalid input.")
            continue
        cooks.append(FastFoodCook(name, hire_date, shift))
        i += 1

    max_date = Date(2019, 1, 1)

    valid_cooks = []

    for cook in cooks:
        if cook.shift != Shift.DAY:
            continue
        if cook.hire_date < max_date:
            valid_cooks.append(cook)
    
    print("Valid cooks:")
    for cook in valid_cooks:
        print(cook.name)

if __name__ == "__main__":
    main()