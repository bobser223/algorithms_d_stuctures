
"""
Реалізуйте каталог деякої бібліотеки.
Бібліотека може містити кілька книг одного автора.
"""


EMPTY = "EMPTY"
DELETED = "DELETED"
size: int = 100
count: int = 0
authors: list[str]
books: list[str]


def is_prime(n: int) -> bool:
    if n <= 1:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


def rehash():
    global count, size, books, authors
    old_authors = authors
    old_books = books
    old_size = size

    size = size * 2 + 1
    while not is_prime(size):
        size = size * 2 + 1

    count = 0
    init()

    for i in range(old_size):
        if old_authors[i] not in (EMPTY, DELETED):
            addBook(old_authors[i], old_books[i])


def _hash(string: str) -> int:
    h = 0
    for i in range(len(string)):
        h = h * 31 + ord(string[i])
    return h % size


def init():
    """ Викликається 1 раз на початку виконання програми. """
    global authors, books, count
    authors = [EMPTY] * size
    books = [EMPTY] * size
    count = 0


def addBook(author: str, title: str):
    """ Додає книгу до бібліотеки.
    :param author: Автор книги
    :param title: Назва книги
    """

    global authors, books, size, count

    if size*0.7 < count:
        rehash()

    i = _hash(author)
    while books[i] not in (EMPTY, DELETED):
        if authors[i] == author and books[i] == title:
            return
        i = (i + 1) % size

    count += 1
    authors[i] = author
    books[i] = title


def find(author, title):
    """ Перевірає чи міститься задана книга у бібліотеці.
    :param author: Автор
    :param title: Назва книги
    :return: True, якщо книга міститься у бібліотеці та False у іншому разі.
    """

    global authors, books, size, count

    i = _hash(author)

    while authors[i] != EMPTY:
        if authors[i] != DELETED:
            if authors[i] == author and books[i] == title:
                return True
        i = (i + 1) % size

    return False


def delete(author, title):
    """ Видаляє книгу з бібліотеки.
    :param author: Автор
    :param title: Назва книги
    """

    global authors, books, size, count
    i = _hash(author)
    while authors[i] != EMPTY:
        if authors[i] != DELETED:
            if authors[i] == author and books[i] == title:
                authors[i] = DELETED
                books[i] = DELETED
                count -= 1
                return
        i = (i + 1) % size


def findByAuthor(author):

    lst = []

    global authors, books, size, count

    i = _hash(author)
    while authors[i] != EMPTY:
        if authors[i] != DELETED and authors[i] == author:
            lst.append(books[i])
        i = (i + 1) % size

    return lst


if __name__ == "__main__":
    init()
    print(books)
    print(authors)
    addBook("A", 'a')
    addBook("A", 'b')
    addBook("A", 'c')
    # print(books)
    # print(authors)
    delete("A", 'a')
    print(books)
    print(authors)
    print(findByAuthor("A"))
    addBook("B", 'ab')
    print(books)
    print(authors)
    delete("B", 'ab')
    print(books)
    print(authors)