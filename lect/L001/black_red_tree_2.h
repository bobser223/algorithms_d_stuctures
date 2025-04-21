//
// Created by Volodymyr Avvakumov on 31.03.2025.
//

#ifndef ALG_D_SRUCT_BLACK_RED_TREE_H
#define ALG_D_SRUCT_BLACK_RED_TREE_H

#define BLACK false
#define RED true

#endif //ALG_D_SRUCT_BLACK_RED_TREE_H

#include <iostream>

/*
 * ЧЕРВОНО-ЧОРНЕ ДЕРЕВО:
 *  - Кожна вершина або червона, або чорна.
 *  - Корінь дерева завжди чорний.
 *  - Усі NIL-вказівники (тобто відсутні діти) вважаються чорними вершинами.
 *  - Якщо вершина червона, тоді її батько обов'язково чорний.
 *  - Для кожної вершини всі шляхи від неї до нащадків-NIL містять однакову кількість чорних вершин.
 *
 * Ці умови дозволяють тримати дерево максимально збалансованим (за висотою),
 * забезпечуючи вставку, пошук і видалення в середньому за O(log n).
 */

struct Node {
    int key;
    int value;

    Node* parent;
    Node* left;
    Node* right;

    bool color;

    Node() {
        color = BLACK;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        key = 0;
        value = 0;
    }

    Node(int key, int value) {
        this->key = key;
        this->value = value;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

// Спеціальний "ніби-порожній" вузол (NIL). Він використовується як сторож (sentinel).
// Будь-яке звертання до .left / .right, коли їх "немає", насправді буде вказувати на NIL.
Node* NIL = new Node{};

class Tree {
private:
    Node* root;

    /*
     * Ініціалізуємо новий вузол:
     *  - ключ і значення
     *  - колір за замовчуванням червоний (RED)
     *  - усі покажчики вказують на NIL (щоб вузол був коректно інтегрований)
     */
    static void initNode(Node* node, int key, int value){
        node->key = key;
        node->value = value;
        node->left = NIL;
        node->right = NIL;
        node->parent = NIL;
        node->color = RED;
    }

    // Перевіряємо, що вузол не є NIL.
    static bool exists(Node* n){
        return n != NIL;
    }

    /*
     * Лівий поворот:
     *   Здійснюється довкола вузла x, де y = x->right.
     *   Ми робимо "підйом" y на місце x, а x "опускаємо" вліво від y.
     *
     *   Передумова: x->right != NIL
     *
     *         x               y
     *          \             / \
     *           y     ->    x   ?
     *          /             \
     *         ?               ?
     *
     * Великі шматки робимо докладно:
     *  1) Зв’язок x->right = y->left (бо ліва гілка y "переноситься" вправо від x).
     *  2) Якщо y->left існує, оновлюємо її батька (-> x).
     *  3) Зв’язок y->parent = x->parent (y тепер займає місце x у дереві).
     *  4) Оновлюємо вказівники у батька x, щоб він замість x тепер посилався на y.
     *  5) Робимо x "лівим сином" y.
     *  6) Зв’язок x->parent = y.
     */
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    /*
     * Правий поворот (дзеркальний варіант лівого):
     *   Здійснюється довкола вузла x, де y = x->left.
     *   Ми робимо "підйом" y на місце x, а x "опускаємо" вправо від y.
     *
     *   Передумова: x->left != NIL
     *
     *         x              y
     *        /              / \
     *       y       ->     ?   x
     *        \                /
     *         ?              ?
     *
     * Аналогічна логіка:
     *  1) Перенаправляємо x->left на y->right.
     *  2) Якщо y->right існує, оновлюємо її батька на x.
     *  3) y->parent = x->parent (y стає на місце x).
     *  4) Вказівник батька x тепер вказує на y замість x.
     *  5) y->right = x
     *  6) x->parent = y
     */
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    /*
     * Функція balance:
     *  - Викликається після вставки нового червоного вузла.
     *  - Виправляє можливі порушення (батько та дідусь можуть мати проблеми, якщо батько був червоним).
     *
     * Основні випадки (саме тут червоно-чорне дерево "виправляє" свій колір та структуру):
     *   1) Якщо дядько вузла (uncle) червоний – ми просто перекфарбовуємо батька, дядька у чорний,
     *      а дідуся у червоний і рухаємось догори (new_node = grandparent).
     *   2) Якщо дядько чорний, а новий вузол – "правий син" (чи "лівий син" у правій гілці),
     *      робимо поворот та перестановку кольорів (залежно від конкретного випадку).
     */
    void balance(Node* new_node){
        Node* uncle;
        // Поки батько "нового" вузла теж червоний, є ризик порушення правил
        while (new_node->parent->color == RED) {
            // Якщо батько є "лівим сином" дідуся
            if (new_node->parent == new_node->parent->parent->left){
                uncle = new_node->parent->parent->right;
                // 1) Дядько червоний: перекрашуємо і рухаємось угору
                if (uncle->color == RED){
                    new_node->parent->color = BLACK;
                    uncle->color = BLACK;
                    new_node->parent->parent->color = RED;
                    new_node = new_node->parent->parent;
                }
                    // 2) Дядько чорний: можливо, потрібні повороти
                else {
                    // Якщо новий вузол – правий син (лівий випадок)
                    if (new_node == new_node->parent->right) {
                        new_node = new_node->parent;
                        leftRotate(new_node);
                    }
                    // Змінюємо колір батька і дідуся
                    new_node->parent->color = BLACK;
                    new_node->parent->parent->color = RED;
                    rightRotate(new_node->parent->parent);
                }
            }
                // Дзеркальний випадок, якщо батько є "правим сином"
            else {
                uncle = new_node->parent->parent->left;
                if (uncle->color == RED) {
                    new_node->parent->color = BLACK;
                    uncle->color = BLACK;
                    new_node->parent->parent->color = RED;
                    new_node = new_node->parent->parent;
                } else {
                    if (new_node == new_node->parent->left){
                        new_node = new_node->parent;
                        rightRotate(new_node);
                    }
                    new_node->parent->color = BLACK;
                    new_node->parent->parent->color = RED;
                    leftRotate(new_node->parent->parent);
                }
            }
            // Якщо дістались кореня, зупиняємось
            if (new_node == root) {
                break;
            }
        }
        // Корінь завжди має бути чорним
        root->color = BLACK;
    }

    // Рахує кількість дітей (не NIL) у вузла.
    static int childrenCount(Node* node){
        int count = 0;
        if (exists(node->left)) count++;
        if (exists(node->right)) count++;
        return count;
    }

    // Пошук вузла за ключем (повертає вказівник на вузол або NIL).
    Node* searchKey(int key){
        Node* curr = root;
        while (curr != NIL) {
            if (curr->key == key) {
                return curr;
            }
            if (key < curr->key) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return NIL;
    }

    // Повертає мінімальний вузол у піддереві (найлівіший вузол).
    static Node* Min(Node* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    // Повертає єдину дитину вузла, якщо вона існує, або NIL (якщо у вузла менше ніж 2 дітей).
    static Node* childOrMock(Node* node){
        return (exists(node->left) ? node->left : node->right);
    }

    /*
     * Функція "пересаджування" вузлів:
     *  - Заміщує вузол to_node вузлом from_node, під'єднуючи from_node до батька to_node.
     *  - Використовується при видаленні (коли вирізаємо вузол з дерева).
     */
    void transplantNode(Node* to_node, Node* from_node){
        if (to_node->parent == NIL) {
            root = from_node;
        }
        else if (to_node == to_node->parent->left) {
            to_node->parent->left = from_node;
        }
        else {
            to_node->parent->right = from_node;
        }
        from_node->parent = to_node->parent;
    }

    /*
     * Відновлюємо баланс після видалення чорного вузла:
     *  - Якщо видаляється чорний вузол, може бути порушена умова, що "всі шляхи
     *    від вершини до NIL містять однакове число чорних вузлів".
     *  - Ця функція "підтягує" чорний колір вгору і робить повороти/перефарбування
     *    для відновлення коректних умов.
     *
     * Типові кроки:
     *   1) Перевіряємо "брата" (sibling) поточного вузла.
     *   2) Якщо брат червоний, робимо поворот і перекрашуємо, щоб отримати чорного брата.
     *   3) Якщо брат і його діти чорні, перекрашуємо брата у червоний і підіймаємось до батька.
     *   4) Інакше робимо ротації для виправлення ситуації (залежно від того, яка дитина брата чорна/червона).
     */
    void fixBalanceAfterDeleting(Node* node){
        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                Node* brother = node->parent->right;

                // Випадок 1: брат червоний -> робимо поворот, щоб отримати чорного брата
                if (brother->color == RED) {
                    brother->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    brother = node->parent->right;
                }

                // Випадок 2: обидва діти брата чорні
                if (brother->left->color == BLACK && brother->right->color == BLACK) {
                    brother->color = RED;
                    node = node->parent;
                }
                else {
                    // Випадок 3: у брата ліва дитина червона, а права – чорна
                    if (brother->right->color == BLACK) {
                        brother->left->color = BLACK;
                        brother->color = RED;
                        rightRotate(brother);
                        brother = node->parent->right;
                    }
                    // Випадок 4: у брата права дитина червона
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->right->color = BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            }
                // Дзеркальний випадок
            else {
                Node* brother = node->parent->left;
                if (brother->color == RED) {
                    brother->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    brother = node->parent->left;
                }
                if (brother->right->color == BLACK && brother->left->color == BLACK) {
                    brother->color = RED;
                    node = node->parent;
                }
                else {
                    if (brother->left->color == BLACK) {
                        brother->right->color = BLACK;
                        brother->color = RED;
                        leftRotate(brother);
                        brother = node->parent->left;
                    }
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->left->color = BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

    /*
     * Рекурсивна допоміжна функція для виведення дерева "боком" (sideways).
     * Параметр `space` керує відступами, щоб візуально бачити ієрархію.
     */
    void printTreeHelper(Node* node, int space) const {
        if (node == NIL) return;

        // Крок 1: збільшуємо відступ
        space += 5;

        // Крок 2: спершу виводимо праве піддерево
        printTreeHelper(node->right, space);

        // Крок 3: виводимо відступи + інформацію про вузол (key, value, колір)
        std::cout << std::string(space, ' ')
                  << "K:" << node->key << " V:" << node->value
                  << (node->color == RED ? " (R)" : " (B)")
                  << "\n";

        // Крок 4: тепер виводимо ліве піддерево
        printTreeHelper(node->left, space);
    }


public:
    Tree(){
        // Ініціалізуємо корінь в NIL (порожнє дерево).
        // Це важливо для коректної роботи "balance" та інших функцій.
        root = NIL;
    }

    /*
     * INSERT (вставка нового вузла за заданим key, value).
     *  1) Звичайна бінарна вставка (шукаємо місце в дереві).
     *  2) Створюємо червоний вузол (new_node).
     *  3) Викликаємо balance(new_node), щоб, у разі порушень, дерево відновилося.
     */
    void insert(int key, int value){
        Node* curr_node = root;
        Node* parent = NIL;

        // Рухаємось деревом, шукаючи, куди приєднати новий вузол
        while (exists(curr_node)) {
            parent = curr_node;
            if (key < curr_node->key) {
                curr_node = curr_node->left;
            } else {
                curr_node = curr_node->right;
            }
        }

        // Створюємо новий вузол
        Node* new_node = new Node;
        initNode(new_node, key, value);
        new_node->parent = parent;

        // Якщо дерево було порожнім
        if (parent == NIL) {
            root = new_node;
        }
        else if (key < parent->key) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        // Виклик балансу (можливо, ми порушили забарвлення)
        balance(new_node);
    }

    /*
     * POP (видалення з дерева за ключем).
     *   1) Шукаємо вузол за ключем.
     *   2) Якщо не знайдено – завершуємо.
     *   3) Якщо у вузла менше 2 дітей – спрощений випадок (трансплантація).
     *   4) Інакше шукаємо мінімум у правому піддереві (min_node), переносимо його key/value
     *      у вузол, який видаляємо, і видаляємо min_node.
     *   5) Якщо видаляємо чорний вузол, треба викликати fixBalanceAfterDeleting.
     */
    void pop(int key){
        Node* node_to_delete = searchKey(key);
        if (!exists(node_to_delete)) return;  // Нічого не робимо, якщо не знайшли

        Node* temp = node_to_delete;
        bool originalColor = temp->color;
        Node* child;

        // Випадок: вузол має < 2 дітей
        if (childrenCount(node_to_delete) < 2) {
            child = childOrMock(node_to_delete);
            transplantNode(node_to_delete, child);
        }
            // Інакше шукаємо мінімум у правому піддереві
        else {
            Node* min_node = Min(node_to_delete->right);
            temp = min_node;
            originalColor = temp->color;

            // "Фізично" переносимо ключ і значення
            node_to_delete->key = min_node->key;
            node_to_delete->value = min_node->value;

            child = childOrMock(min_node);
            transplantNode(min_node, child);
        }

        // Якщо видаляли чорний вузол, виправляємо баланс
        if (originalColor == BLACK){
            fixBalanceAfterDeleting(child);
        }
    }

    // Публічний метод для друку дерева в консоль
    void printTree() const {
        if (root == NIL) {
            std::cout << "Tree is empty.\n";
        } else {
            printTreeHelper(root, 0);
        }
        std::cout << std::endl;
    }
};