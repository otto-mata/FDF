import sys


def parse(lines: list[list[str]]):
    parsed: list[list[tuple[int, str]]] = []
    tmp: tuple[int, str]
    for l in lines:
        tmp_l: list[tuple[int,str]] = []
        for s in l:
            if s.find(",") >= 0:
                s_parts = s.split(",")
                tmp = (int(s_parts[0]), s_parts[1])
            else:
                tmp = (int(s), None)
            tmp_l.append(tmp)
        parsed.append(tmp_l)
    return parsed


def main():
    file_content: list[str]
    if len(sys.argv) != 2:
        exit(1)
    try:
        with open(sys.argv[1], "r") as f:
            file_content = f.readlines()
    except Exception as e:
        print(f"An exception occured while opening the map: {e}")
    split = []
    for ls in file_content:
        split.append(ls.split())
    parsed = parse(split)
    print(parsed)


if __name__ == "__main__":
    main()
