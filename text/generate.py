# A simple script that generates a txt file of TARGET_SZIE

import os
import sys
import string
import random

TARGET_SIZE = 300 # 300 MB
BUFFER_SIZE = 2**16

def generate_random(length: int) -> str:
    letters = string.ascii_letters
    return "".join(random.choice(letters) for _ in range(length))


def main(args) -> None:
    print(args)
    if len(args) < 2:
        raise ValueError(f"usage: python3 {args[0]} <filename>")

    filename = args[1]

    with open(filename, "a+", encoding="utf-8") as file:
        print("generating...")
        while True:
            if os.path.getsize(filename) / (1024*1024) > 300:
                print("in bytes:" ,os.path.getsize(filename))
                print("in MB: ", os.path.getsize(filename) / (1024*1024))
                break
            chunk = generate_random(BUFFER_SIZE)
            file.write(chunk)


if __name__ == "__main__":
    main(sys.argv)
