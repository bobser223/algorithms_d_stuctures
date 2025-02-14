"""
Реалізуйте каталог деякої бібліотеки.
Бібліотека може містити кілька книг одного автора.
"""


count: int = 0

size: int = 100003
slots: list[str]


def _hash(string: str) -> int:
    h = 0
    for i in range(len(string)):
        h = h * 31 + ord(string[i])
    return h % size


class Node:
    def __init__(self, author,  title):
        self.author: str = author
        self.title: str = title
        self.next: [Node| None] = None



def init():
    """ Викликається 1 раз на початку виконання програми. """
    global slots, count

    slots = [None] * size



def addBook(author, title):
    """ Додає книгу до бібліотеки.
    :param author: Автор книги
    :param title: Назва книги
    """
    global slots, count

    i = _hash(author)

    curr_node = slots[i]

    while curr_node is not None:
        if curr_node.author == author and curr_node.title == title:
            return
        curr_node = curr_node.next

    count += 1
    new_node = Node(author, title)
    new_node.next = slots[i]
    slots[i] = new_node


def find(author, title):
    """ Перевірає чи міститься задана книга у бібліотеці.
    :param author: Автор
    :param title: Назва книги
    :return: True, якщо книга міститься у бібліотеці та False у іншому разі.
    """
    global slots, count
    i = _hash(author)
    curr_node = slots[i]

    while curr_node is not None:
        if curr_node.author == author and curr_node.title == title:
            return True
        curr_node = curr_node.next

    return False


def delete(author, title):
    """ Видаляє книгу з бібліотеки.
    :param author: Автор
    :param title: Назва книги
    """
    global slots, count
    i = _hash(author)
    curr_node = slots[i]

    if curr_node is None:
        # count -= 1
        return

    if curr_node.author == author and curr_node.title == title:
        slots[i] = curr_node.next
        count -= 1
        return

    prev = curr_node
    while curr_node is not None:
        if curr_node.title == title and curr_node.author == author:
            prev.next = curr_node.next
            count -= 1
            return
        prev = curr_node
        curr_node = curr_node.next




def findByAuthor(author):
    """ Повертає список книг заданого автора.
    Якщо бібліотека не міститься книг заданого автора, то підпрограма повертає порожній список.
    :param author: Автор
    :return: Список книг заданого автора у алфавітному порядку.
    """

    result = []

    global slots, count
    i = _hash(author)
    curr_node = slots[i]

    while curr_node is not None:
        if curr_node.author == author:
            result.append(curr_node.title)
        curr_node = curr_node.next

    return result
