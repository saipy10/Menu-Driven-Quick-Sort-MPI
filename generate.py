import random

product_names = [
    "Laptop", "Mobile", "Keyboard", "Mouse", "Monitor",
    "Headphones", "Tablet", "Speaker", "Camera", "Printer",
    "Charger", "SSD", "Pendrive", "Smartwatch", "Router",
    "Projector", "Mic", "Drone", "TV", "PowerBank"
]

brands = [
    "Dell", "HP", "Lenovo", "Apple", "Samsung",
    "Sony", "Asus", "Acer", "Logitech", "Boat"
]

with open("input.txt", "w", encoding="utf-8") as file:

    for i in range(100000):
        name = random.choice(brands) + " " + random.choice(product_names) + " " + str(i+1)

        price = round(random.uniform(500, 150000), 2)

        rating = round(random.uniform(1.0, 5.0), 1)

        file.write(f"{name}|{price}|{rating}\n")

print("input.txt with 100000 mock records generated successfully.")