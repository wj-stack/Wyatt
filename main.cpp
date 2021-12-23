#include <bits/stdc++.h>

#include <utility>


using namespace std;

class BookType {
private:
    map<char, const char *> type{
            {'A', "���˼���塢�������塢ë��˼�롢��Сƽ����"},
            {'B', "��ѧ���ڽ�"},
            {'C', "����ѧ����"},
            {'D', "���Ρ�����"},
            {'E', "����"},
            {'F', "����"},
            {'G', "�Ļ�����ѧ������������"},
            {'H', "���ԡ�����"},
            {'I', "��ѧ"},
            {'J', "����"},
            {'K', "��ʷ������"},
            {'N', "��Ȼ��ѧ����"},
            {'O', "�����ѧ�ͻ�ѧ"},
            {'P', "����ѧ�������ѧ"},
            {'Q', "�����ѧ"},
            {'R', "ҽҩ������"},
            {'S', "ũҵ��ѧ"},
            {'T', "��ҵ����"},
            {'U', "��ͨ����"},
            {'V', "���ա�����"},
            {'X', "������ѧ���Ͷ�������ѧ(��ȫ��ѧ)"},
            {'Z', "�ۺ���ͼ��"}
    };
public:
    const char *getCategory(const char c) {
        return type[c];
    }
};

BookType bookType;

class Book {
public:

    using ptr = shared_ptr<Book>;

    Book(){

    }


    Book(string bookName, string author, int id, char category, bool isBorrow = false) : bookName(std::move(bookName)),
                                                                                         author(std::move(author)),
                                                                                         id(id),
                                                                                         category(category),
                                                                                         isBorrow(isBorrow) {}

    string bookName;
    // ����
    string author; // ����
    int id{}; // ���� ����Ψһ�� ��ͬ������Ҳ��ͬ
    char category{}; // ����
    bool isBorrow = false; // �Ƿ���ȥ��

};

class BookManager {
public:
    // ����鼮
    bool add(const Book::ptr &book) {
        if (ids.count(book->id))return false;
        books.push_back(book);
        stock[book->bookName]++;
        return true;
    }

    // ɾ���鼮
    bool del(int id) {
        for (auto it = books.begin(); it != books.end(); it++) {
            if ((*it)->id == id) {
                books.erase(it);
                return true;
            }
        }
        return false;
    }

    // ��ѯ�鼮
    auto query(const Book &q) -> shared_ptr<vector<Book::ptr>> {
        shared_ptr<vector<Book::ptr>> queryBook(new vector<Book::ptr>);
        for (auto &book:books) {
            if (book->bookName.find(q.bookName) != string::npos ||
                book->author.find(q.author) != string::npos) {
                queryBook->push_back(book);

            }
        }
        return queryBook;
    }

    Book::ptr find(int id)
    {
        for (auto normalIterator = books.begin(); normalIterator != books.end(); ++normalIterator) {
            if((*normalIterator)->id == id)
            {
                return *normalIterator;
            }
        }
        return nullptr;
    }

    // �����鼮
    bool borrowBook(Book::ptr book) {
        if (stock[book->bookName] <= 0)return false;
        book->isBorrow = true;
        stock[book->bookName]--;
        return true;
    }

    // �黹�鼮
    bool backBook(Book::ptr book) {
        book->isBorrow = false;
        stock[book->bookName]++;
    }

    void printAllBooks() {
        const char *p[] = {"���", "����", "����", "����", "״̬"};
        printf("%4s %40s %15s %40s %6s\n", p[0], p[1], p[2], p[3], p[4]);
        for (auto &book:books) {
            printf("%4d %40s %15s %40s %6s\n", book->id, book->bookName.c_str(), book->author.c_str(),
                   bookType.getCategory(book->category), (book->isBorrow ? "���" : "�ڲ�"));
        }
    }

    void printBooks(const shared_ptr<vector<Book::ptr>> &ptr) {
        const char *p[] = {"���", "����", "����", "����", "״̬"};
        printf("%4s %40s %15s %40s %6s\n", p[0], p[1], p[2], p[3], p[4]);
        for (auto &book:*ptr) {
            printf("%4d %40s %15s %40s %6s\n", book->id, book->bookName.c_str(), book->author.c_str(),
                   bookType.getCategory(book->category), (book->isBorrow ? "���" : "�ڲ�"));
        }
    }

    void printBook(const Book::ptr &book) {
        const char *p[] = {"���", "����", "����", "����", "״̬"};
        printf("%4s %40s %15s %40s %6s\n", p[0], p[1], p[2], p[3], p[4]);
        printf("%4d %40s %15s %40s %6s\n", book->id, book->bookName.c_str(), book->author.c_str(),
               bookType.getCategory(book->category), (book->isBorrow ? "���" : "�ڲ�"));

    }

private:
    vector<Book::ptr> books; // �����鼮
    map<string, int> stock; // ��� <����,����>
    set<int> ids; // ��ż���
};


class Member {
public:
    using ptr = shared_ptr<Member>;

    int myId;
    string name;

    Member(string name) : name(std::move(name)) {
        ids++;
        myId = ids;
    }

    Member(int id ,string name) : name(std::move(name)),myId(id) {
    }

    void addRecord(const Book::ptr &ptr) {
        records.push_back(ptr);
    }

    void printRecords()
    {
        printf("�����¼��\n");

        for (auto it = records.begin(); it != records.end(); ++it) {
            printf("    �鼮���:%d ����:%s\n",(*it)->id,(*it)->bookName.c_str());
        }
    }

public:
    static int ids ;
    vector<Book::ptr> records; // �����¼
};

int Member::ids = 0;

class MemberManager {
public:

    void add(const Member::ptr &ptr) {
        members.push_back(ptr);
    }

    bool del(const Member::ptr &ptr) {
        for (auto normalIterator = members.begin(); normalIterator != members.end(); ++normalIterator) {
            if (*normalIterator == ptr) {
                members.erase(normalIterator);
                return true;
            }
        }
        return false;
    }

    // ��ѯ��Ա
    auto query(const Member::ptr &q) -> shared_ptr<vector<Member::ptr>> {
        shared_ptr<vector<Member::ptr>> queryMember(new vector<Member::ptr>);
        for (auto &member:members) {
            if (member->name.find(q->name) != string::npos
                || member->myId == q->myId) {
                queryMember->push_back(member);
            }
        }
        return queryMember;
    }

    Member::ptr find(int memberId)
    {
        for (auto normalIterator = members.begin(); normalIterator != members.end(); ++normalIterator) {
            if((*normalIterator)->myId == memberId)
            {
                return *normalIterator;
            }
        }
        return nullptr;
    }

    void printMembers(shared_ptr<vector<Member::ptr>>& members)
    {
        for (auto it = members->begin(); it != members->end(); it++) {
            printf("��Ա���:%d ����:%s\n",(*it)->myId,(*it)->name.c_str());
            (*it)->printRecords();
        }
    }

    void printAllMember()
    {
        printf("��Ա��� ����");
        for (auto it = members.begin(); it != members.end(); it++) {
            printf("%4d :%10s\n",(*it)->myId,(*it)->name.c_str());
        }
    }


    void printAllMemberRecord()
    {
        for (auto it = members.begin(); it != members.end(); it++) {
            printf("��Ա���:%d ����:%s\n",(*it)->myId,(*it)->name.c_str());
            (*it)->printRecords();
        }
    }

private:
    vector<Member::ptr> members;
};

void clear() {
//    system("cls");
}


BookManager bookManager;
MemberManager memberManager;

void beginUi();

void MemberManagerUi() {
    clear();
    printf("��Ա�����ܣ�\n");
    printf("1.���ӻ�Ա \n");
    printf("2.ɾ����Ա \n");
    printf("3.��ѯ��Ա \n");
    printf("4.�鿴���л�Ա \n");
    printf("5.�鿴���л�Ա������Ϣ \n");
    int n;
    cin >> n;
    if (n == 1) {
        printf("��ӻ�Ա: ����\n");
        string name;
        cin >> name;
        Member::ptr member(new Member(name));
        printf("��ӻ�Ա�ɹ�!\n");
    }else if(n == 2){
        printf("ɾ����ʽ: ID\n");
        int memberId;
        cin >> memberId ;
        auto member = memberManager.find(memberId);
        memberManager.del(member);
    }else if(n == 3)
    {
        printf("��ѯ��ʽ: ���� ID\n");
        string name;
        int memberId;
        cin >>name  >>memberId ;
        Member::ptr member(new Member(memberId,name));
        auto members = memberManager.query(member);
        memberManager.printMembers(members);
    }else if(n == 4)
    {
        memberManager.printAllMember();
    }else if(n == 5)
    {
        memberManager.printAllMemberRecord();
    }else
    {
        beginUi();
        return;
    }
    MemberManagerUi();
}

void BookManagerUi() {
    clear();
    printf("ͼ����Ĺ��ܣ�\n");
    printf("1.����ͼ�� \n");
    printf("2.ɾ��ͼ�� \n");
    printf("3.��ѯͼ�� \n");
    printf("4.ͼ����� \n");
    printf("5.���� \n");
    printf("6.�鿴�����鼮 \n");

    int n;
    cin >> n;
    if (n == 1) {
        printf("�鼮��ʽ: ��� ���� ���� ����\n");
        Book book;
        cin >> book.id >> book.bookName >> book.author >> book.category;
        Book::ptr bookPtr;
        bookPtr.reset(&book);
        if (bookManager.add(bookPtr)) {
            printf("����鼮�ɹ�!\n");
        } else printf("����鼮ʧ��!\n");

    } else if (n == 2) {
        printf("ɾ����ʽ: ���\n");
        int bookId;
        cin >> bookId;
        bookManager.del(bookId);
        if(bookManager.del(bookId)){
            printf("ɾ�����ɹ�!\n");
        } else printf("ɾ���鼮ʧ��!\n");
    }else if(n == 3){
        printf("��ѯ��ʽ:  ���� ���� \n");
        Book book;
        cin >> book.bookName >> book.author;
        auto books = bookManager.query(book);
        bookManager.printBooks(books);
    }else if(n == 4)
    {
        printf("���ĸ�ʽ: ͼ���� ��Ա���\n");
        int bookId,memberId;
        cin >> bookId >> memberId;
        Member::ptr member = memberManager.find(memberId);
        Book::ptr book = bookManager.find(bookId);
        if(book && member)
        {
            member->addRecord(book);
            printf("�û���%15s ��� %25s\n",member->name.c_str(),book->bookName.c_str());
        }
    }else if(n == 5)
    {
        printf("�����ʽ: ͼ����\n");
        int bookId;
        cin >> bookId ;
        Book::ptr book = bookManager.find(bookId);
        if(book)
        {
            if(bookManager.backBook(book))
            {
                printf("����ɹ�!\n");
            } else printf("����ʧ��!\n");

        }

    }else if(n == 6)
    {
        bookManager.printAllBooks();
    }else{
        beginUi();
        return;
    }
    BookManagerUi();

}

void beginUi() {
    printf("ͼ����Ĺ���ϵͳ\n");
    printf("1.ͼ�����\n");
    printf("2.��Ա����\n");
    int n;
    scanf("%d", &n);
    if (n == 1) {
        BookManagerUi();
    } else if (n == 2) {
        MemberManagerUi();
    }
}

int main() {
    int id = 6851;
//    Book::ptr book(new Book("����","����",id++,'A'));
    for (int i = 0; i < 10; ++i) {
        bookManager.add(Book::ptr(new Book("����" + to_string(i), to_string(i),id++,'A' + i)));
    }

    for (int i = 0; i < 10; ++i) {
        Member::ptr member(new Member("��Ա" + to_string(i)));
        memberManager.add(member);
        Book::ptr book;
        book = bookManager.find(6851+i);
        bookManager.borrowBook(book);
        member->addRecord(book);

    }

    beginUi();

    return 0;
}
