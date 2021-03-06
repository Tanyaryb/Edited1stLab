#pragma once
#include <iostream>

typedef int dataType;   // чтоб можно было выбрать любой тип хранения данных за секунду
enum color { RED, BLACK };


class List
{
private:
	struct NodeList
	{
	public:
		NodeList* next = NULL;
		dataType data;
	};
	NodeList *head;
	NodeList* tail;
public:
	void Next()
	{
		head = head->next;
	}
	dataType getData()
	{
		return head->data;
	}
	bool isEmpty()
	{
		if (head) return false;
		else return true;
	}
	void push_back(dataType data)
	{
		if (tail)
		{
			tail->next = new NodeList;
			tail = tail->next;
			tail->data = data;
		}
		else
		{
			tail = head = new NodeList;
			tail->data = data;
		}
	}
};

struct Node
{
	Node* left;
	Node* right;
	Node* parent;
	color color;
	dataType data;
	dataType key;
};

class Map
{
private:
	class RBtree
	{
	private:
		Node* root;
		void insertfix(Node*);			// балансировка после ввода узла
		void leftrotate(Node*);			// левый  поворот
		void rightrotate(Node*);		// правый поворот
		Node* successor(Node*);			// балансировка
		void delfix(Node*);				// балансировка после удаления узла
		bool display(Node*);			// вывод узла
		void cl(Node* p);
		bool searchbool(dataType x);	// есть такой узел в дереве или нет, дополнение поиска
		void insertpriv(Node* t);			// ввод узла в дерево
		void Destruct(Node* current);	// дополнение к деструктору
	public:
		RBtree() :root(nullptr) {};		// конструктор
		~RBtree();						// деструктор
		void insert(dataType inskey, dataType insdata);			// метод добавления узла в дерево
		bool find(dataType data);						// метод поиска в дереве
		void remove(dataType x);							// метод удаления узла из дерева
		bool print();									// метод вывода всего дерева
		void clear();									// метод очищения ассоциативного массива
		List values;
		List keys;
	};
	RBtree tree;
public:
	void insert(dataType inskey, dataType insdata);			// метод добавления узла в дерево
	bool find(dataType data);						// метод поиска в дереве
	void remove(dataType x);							// метод удаления узла из дерева
	bool print();									// метод вывода всего дерева
	List get_values();								// метод вывода значений
	List get_keys();								// метод вывода ключей
	void clear();									// метод очищения ассоциативного массива
};

void Map::insert(dataType inskey, dataType insdata)
{
	tree.insert(inskey, insdata);
}

bool Map::find(dataType data)
{
	return tree.find(data);
}

void Map::remove(dataType x)
{
	tree.remove(x);
}

bool Map::print()
{
	return tree.print();
}

List Map::get_values()
{
	return tree.values;
}

List Map::get_keys()
{
	return tree.keys;
}

void Map::clear()
{
	tree.clear();
}

Map::RBtree::~RBtree()   // деструктор
{
	if (root != NULL)
	{
		Destruct(root);  // потому что нельзя вызвать деструктор рекурсивно
	}
}

void Map::RBtree::Destruct(Node* current)  // для деструктора -- рекурсивное удаление дерева
{
	if (current != nullptr)
	{
		Destruct(current->left);
		Destruct(current->right);
		delete current;
	}
}



void Map::RBtree::insert(dataType inskey, dataType insdata)  // создание узла -- данные вводятся с клавиатуры
{


	Node* temp = new Node;
	temp->data = insdata;
	temp->key = inskey;
	temp->left = NULL;
	temp->right = NULL;
	temp->color = RED;
	if (searchbool(temp->data))
	{
		delete temp;
	}
	else
	{
		values.push_back(insdata);
		keys.push_back(inskey);
		insertpriv(temp);
	}
}

void Map::RBtree::insertpriv(Node* temp)	// t -- вставляемый в деререво узел
{
	Node* rootCopy = root, *q = NULL;
	if (root == NULL)  // если дерево не существует, то добавляемый узел становится корнем
	{
		root = temp;
		temp->parent = NULL;
	}
	else  // если дерево существует... находим место куда вставить узел
	{
		while (rootCopy != NULL)	// смотрим в дерево, пока не дошли до листов
		{
			q = rootCopy;
			if (rootCopy->data < temp->data)		// если вставляемый больше корня/узла то ГО в правое поддерево
				rootCopy = rootCopy->right;
			else								// иначе ГО в левое поддерево
				rootCopy = rootCopy->left;
		}
		temp->parent = q;						// q усонавливает temp
		if (q->data < temp->data)				// исходя из значения temp, ставим либо правым
			q->right = temp;
		else								// либо левым потомком q
			q->left = temp;
	}
	insertfix(temp);	// балансируем, перекрашиваем, делаем повороты...
}

void Map::RBtree::insertfix(Node* temp)
{
	Node* uncle = NULL;
	if (root == temp) // если в дереве только данный узел красим в ченое и все
	{
		temp->color = BLACK;
		temp->parent = NULL;
		return;
	}
	// иначе
	while (temp->parent != NULL && temp->parent->color == RED)
	{
		Node* grandpa = temp->parent->parent;	// дед
		if (grandpa->left == temp->parent)		// если отец temp левый потомок деда
		{
			if (grandpa->right != NULL)		// и при этом нет правого потомка
			{
				uncle = grandpa->right;		// тогда дядя правый потомок деда
				if (uncle->color == RED)	// и если красный
				{
					temp->parent->color = BLACK;	// то отец temp -- черный
					uncle->color = BLACK;		// дядя тоже черный
					grandpa->color = RED;		// дед красный
					temp = grandpa;
				}
			}
			else  // если оба потомка существуют...
			{
				if (temp->parent->right == temp)  // если temp правый потомок отца, тогда левый поворот от отца
				{
					temp = temp->parent;
					leftrotate(temp);
				}
				temp->parent->color = BLACK;	// отец черный
				grandpa->color = RED;		// дед красный
				rightrotate(grandpa);		// правый поворот от деда
			}
		}
		else  // если отец temp правый потомок деда, тоже самое зеркально отображенное...
		{
			if (grandpa->left != NULL)
			{
				uncle = grandpa->left;
				if (uncle->color == RED)
				{
					temp->parent->color = BLACK;
					uncle->color = BLACK;
					grandpa->color = RED;
					temp = grandpa;
				}
			}
			else
			{
				if (temp->parent->left == temp)
				{
					temp = temp->parent;
					rightrotate(temp);
				}
				temp->parent->color = BLACK;
				grandpa->color = RED;
				leftrotate(grandpa);
			}
		}
		// сохраняем свойства корня
		root->color = BLACK;
		root->parent = NULL;
	}
}

void Map::RBtree::remove(dataType data)
{
	if (root == NULL)
	{
		std::cout << "\nПустое дерево, нечего удалить!";
		return;
	}
	Node* p = root;
	Node* lefttemp = NULL;
	Node* q = NULL;
	bool found = false;
	while (p != NULL && found == false)  // ищем
	{
		if (p->key == data)
			found = true;
		if (found == false)
		{
			if (p->key < data)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == false) // не нашли
	{
		std::cout << "\nТакого элемента нет в дереве!";
		return;
	}
	else // нашли, удаляем
	{
		std::cout << "\nУдаленный элемент: " << p->data;
		std::cout << "\nКлюч: " << p->key;
		std::cout << "\nЦвет: ";
		if (p->color == BLACK)
			std::cout << "Черный\n";
		else
			std::cout << "Красный\n";

		if (p->parent != NULL)
			std::cout << "\nРодитель: " << p->parent->data;
		else
			std::cout << "\nУ него нет родителя.  ";
		if (p->right != NULL)
			std::cout << "\nПравый потомок: " << p->right->data;
		else
			std::cout << "\nУ него нет правого потомка.  ";
		if (p->left != NULL)
			std::cout << "\nЛевый потомок: " << p->left->data;
		else
			std::cout << "\nУ него нет левого потомка.  ";

		if (p->left == NULL || p->right == NULL)  // если хотя бы один потомок лист
			lefttemp = p;
		else
			lefttemp = successor(p);
		if (lefttemp->left != NULL)		// если левый потомок существует
			q = lefttemp->left;
		else						// если нет
		{
			if (lefttemp->right != NULL)	// и при этом правый потомок тоже существует
				q = lefttemp->right;
			else					// если нет
				q = NULL;
		}
		if (q != NULL)		// после выше происходящего если q не лист то его отец это отец у тоже
			q->parent = lefttemp->parent;
		if (lefttemp->parent == NULL)			// если нет родителя, то он корень
			root = q;
		else							// иначе
		{
			if (lefttemp == lefttemp->parent->left)	// если lefttemp левый потомок отца
				lefttemp->parent->left = q;
			else						// если правый
				lefttemp->parent->right = q;
		}
		if (lefttemp != p)
		{
			p->color = lefttemp->color;
			p->data = lefttemp->data;
		}
		if (lefttemp->color == BLACK)  // если у был черным, нужно балансировать
			delfix(q);
		std::cout << "\nУзел был удален, дерево - сбалансировано!\n";
	}

}

void Map::RBtree::clear()
{
	cl(root);
}

void Map::RBtree::cl(Node* p)
{
	if (root == NULL)
	{
		std::cout << "\nМассив очищен";
		return;
	}
	Node* y = NULL;
	Node* q = NULL;

	if (p->left != NULL)
		cl(p->left);
	if (p->right != NULL)
		cl(p->right);

	if (p->left == NULL || p->right == NULL)  // если хотя бы один потомок лист
		y = p;
	else
		y = successor(p);
	if (y->left != NULL)		// если левый потомок существует
		q = y->left;
	else						// если нет
	{
		if (y->right != NULL)	// и при этом правый потомок тоже существует
			q = y->right;
		else					// если нет
			q = NULL;
	}
	if (q != NULL)		// после выше происходящего если q не лист то его отец это отец у тоже
		q->parent = y->parent;
	if (y->parent == NULL)			// если нет родителя, то он корень
		root = q;
	else							// иначе
	{
		if (y == y->parent->left)	// если у левый потомок отца
			y->parent->left = q;
		else						// если правый
			y->parent->right = q;
	}
	if (y != p)
	{
		p->color = y->color;
		p->data = y->data;
	}
	if (y->color == BLACK)  // если у был черным, нужно балансировать
		delfix(q);
}

void Map::RBtree::delfix(Node* p)
{
	Node* s = NULL; // дядя
	while (p != root && p->color == BLACK)	// пока не корень и не черный одновременно
	{
		if (p->parent->left == p)	// если р левый потомок
		{
			s = p->parent->right;	// s - дядя
			if (s->color == RED)	// если дядя красный
			{
				s->color = BLACK;		// дядя черный
				p->parent->color = RED;	// отец красный
				leftrotate(p->parent);	// левый поворот от отца
				s = p->parent->right;	// дядя стал правым потомком отца
			}
			if (s->right->color == BLACK && s->left->color == BLACK)  // племянники черные одновременно
			{
				s->color = RED; // тогда дядя красный
				p = p->parent;
			}
			else
			{
				if (s->right->color == BLACK)	//если правый племянник черный
				{
					s->left->color = BLACK; // левый тоже будет
					s->color = RED;			// дядя опять красный
					rightrotate(s);			// правый поворот от дяди
					s = p->parent->right;	// дядя стал правым потомком отца
				}
				s->color = p->parent->color;
				p->parent->color = BLACK;
				s->right->color = BLACK;
				leftrotate(p->parent);
				p = root;
			}
		}
		else  // если р правый потомок, аналогично зеркально отображенно
		{
			s = p->parent->left;
			if (s->color == RED)
			{
				s->color = BLACK;
				p->parent->color = RED;
				rightrotate(p->parent);
				s = p->parent->left;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				p = p->parent;
			}
			else
			{
				if (s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
					leftrotate(s);
					s = p->parent->left;
				}
				s->color = p->parent->color;
				p->parent->color = BLACK;
				s->left->color = BLACK;
				rightrotate(p->parent);
				p = root;
			}
		}
		p->color = BLACK;
		root->color = BLACK;
		root->parent = NULL;
	}
}

void Map::RBtree::leftrotate(Node* p)	// левый поворот
{
	if (p->right == NULL)
		return;
	else
	{
		Node* y = p->right;
		if (y->left != NULL)
		{
			p->right = y->left;
			y->left->parent = p;
		}
		else
			p->right = NULL;
		if (p->parent != NULL)
			y->parent = p->parent;
		if (p->parent == NULL)
			root = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->left = p;
		p->parent = y;
	}
}
void Map::RBtree::rightrotate(Node* p)	// правый поворот
{
	if (p->left == NULL)
		return;
	else
	{
		Node* temp = p->left;
		if (temp->right != NULL)
		{
			p->left = temp->right;
			temp->right->parent = p;
		}
		else
			p->left = NULL;
		if (p->parent != NULL)
			temp->parent = p->parent;
		if (p->parent == NULL)
			root = temp;
		else
		{
			if (p == p->parent->left)
				p->parent->left = temp;
			else
				p->parent->right = temp;
		}
		temp->right = p;
		p->parent = temp;
	}
}

Node* Map::RBtree::successor(Node* p)	// от переданного узла возвращает возвращает 
{
	Node* temp = NULL;					// 1. на NULL если нет потомков; 
	if (p->left != NULL)			// 2. на правый последний элемент левого поддерева
	{
		temp = p->left;
		while (temp->right != NULL)
			temp = temp->right;
	}
	else							// 2. на левый последний элемент правого поддерева
	{
		temp = p->right;
		while (temp->left != NULL)
			temp = temp->left;
	}
	return temp;
}

bool Map::RBtree::print()
{
	return display(root);
}

bool Map::RBtree::display(Node* p)
{
	if (root == NULL)
	{
		std::cout << "\nДерево пусто!.";
		return false;
	}
	if (p != NULL)
	{
		if (p == root)
			std::cout << "\n Корень: ";
		else
			std::cout << " Узел: ";
		std::cout << "\n\tДанные:\t\t" << p->data;
		std::cout << "\n\tКлюч:\t\t" << p->key;
		std::cout << "\n\tЦвет:\t";
		if (p->color == BLACK)
			std::cout << "\tЧерный";
		else
			std::cout << "\tКрасный";
		if (p->parent != NULL)  // && p != root
			std::cout << "\n\tРодитель:\t" << p->parent->data;
		else
			std::cout << "\n\tУ него нет родителя.";
		if (p->right != NULL)
			std::cout << "\n\tПравый потомок:\t" << p->right->data;
		else
			std::cout << "\n\tУ него нет правого потомка.";
		if (p->left != NULL)
			std::cout << "\n\tЛевый потомок:\t" << p->left->data;
		else
			std::cout << "\n\tУ него нет левого потомка.";

		if (p->left)
		{
			std::cout << "\n Левый";
			display(p->left);
		}

		if (p->right)
		{
			std::cout << "\n Правый";
			display(p->right);
		}
		return true;

	}
}

bool Map::RBtree::searchbool(dataType x)		// дополнение для поиска
{
	if (root == NULL)  //Дерево пусто!
		return false;
	Node* p = root;
	bool found = false;
	while (p != NULL && found == false)
	{
		if (p->key == x)
			found = true;
		if (found == false)
		{
			if (p->key < x)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == false)
		return false;	// не нашел 
	else
		return true;	// нашел 
}


bool Map::RBtree::find(dataType foo)
{
	if (root == NULL)
	{
		std::cout << "\nПустое дерево\n";
		return false;
	}
	Node* p = root;
	bool found = false;
	while (p != NULL && found == false)
	{
		if (p->key == foo)
			found = true;
		if (found == false)
		{
			if (p->key < foo)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == false)
	{
		std::cout << "\nЭлемент не найден!";
		return found;
	}
	else
	{
		found = true;
		std::cout << "\n Найденный элемент: ";
		std::cout << "\n\tДанные:\t\t" << p->data;
		std::cout << "\n\tКлюч:\t\t" << p->key;
		std::cout << "\n\tЦвет:\t";
		if (p->color == BLACK)
			std::cout << "\tЧерный";
		else
			std::cout << "\tКрасный";
		if (p->parent != NULL)
			std::cout << "\n\tРодитель:\t" << p->parent->data;
		else
			std::cout << "\n\tУ него нет родителя.";
		if (p->right != NULL)
			std::cout << "\n\tПравый потомок:\t" << p->right->data;
		else
			std::cout << "\n\tУ него нет правого потомка.";
		if (p->left != NULL)
			std::cout << "\n\tЛевый потомок:\t" << p->left->data;
		else
			std::cout << "\n\tУ него нет левого потомка.";
		std::cout << std::endl;
		return found;
	}
}
