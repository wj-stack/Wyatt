#include <bits/stdc++.h>

#include <utility>


using namespace std;

class BookType {
private:
    map<char, const char *> type{
            {'A', "马克思主义、列宁主义、毛泽东思想、邓小平理论"},
            {'B', "哲学、宗教"},
            {'C', "社会科学总论"},
            {'D', "政治、法律"},
            {'E', "军事"},
            {'F', "经济"},
            {'G', "文化、科学、教育、体育"},
            {'H', "语言、文字"},
            {'I', "文学"},
            {'J', "艺术"},
            {'K', "历史、地理"},
            {'N', "自然科学总论"},
            {'O', "数理科学和化学"},
            {'P', "天文学、地球科学"},
            {'Q', "生物科学"},
            {'R', "医药、卫生"},
            {'S', "农业科学"},
            {'T', "工业技术"},
            {'U', "交通运输"},
            {'V', "航空、航天"},
            {'X', "环境科学、劳动保护科学(安全科学)"},
            {'Z', "综合性图书"}
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
    // 书名
    string author; // 作者
    int id{}; // 书编号 具有唯一性 相同的书编号也不同
    char category{}; // 分类
    bool isBorrow = false; // 是否借出去了

};

class BookManager {
public:
    // 添加书籍
    bool add(const Book::ptr &book) {
        if (ids.count(book->id))return false;
        books.push_back(book);
        stock[book->bookName]++;
        return true;
    }

    // 删除书籍
    bool del(int id) {
        for (auto it = books.begin(); it != books.end(); it++) {
            if ((*it)->id == id) {
                books.erase(it);
                return true;
            }
        }
        return false;
    }

    // 查询书籍
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

    // 借阅书籍
    bool borrowBook(Book::ptr book) {
        if (stock[book->bookName] <= 0)return false;
        book->isBorrow = true;
        stock[book->bookName]--;
        return true;
    }

    // 归还书籍
    bool backBook(Book::ptr book) {
        book->isBorrow = false;
        stock[book->bookName]++;
    }

    void printAllBooks() {
        const char *p[] = {"编号", "书名", "作者", "分类", "状态"};
        printf("%4s %40s %15s %40s %6s\n", p[0], p[1], p[2], p[3], p[4]);
        for (auto &book:books) {
            printf("%4d %40s %15s %40s %6s\n", book->id, book->bookName.c_str(), book->author.c_str(),
                   bookType.getCategory(book->category), (book->isBorrow ? "借出" : "在册"));
        }
    }

    void printBooks(const shared_ptr<vector<Book::ptr>> &ptr) {
        const char *p[] = {"编号", "书名", "作者", "分类", "状态"};
        printf("%4s %40s %15s %40s %6s\n", p[0], p[1], p[2], p[3], p[4]);
        for (auto &book:*ptr) {
            printf("%4d %40s %15s %40s %6s\n", book->id, book->bookName.c_str(), book->author.c_str(),
                   bookType.getCategory(book->category), (book->isBorrow ? "借出" : "在册"));
        }
    }

    void printBook(const Book::ptr &book) {
        const char *p[] = {"编号", "书名", "作者", "分类", "状态"};
        printf("%4s %40s %15s %40s %6s\n", p[0], p[1], p[2], p[3], p[4]);
        printf("%4d %40s %15s %40s %6s\n", book->id, book->bookName.c_str(), book->author.c_str(),
               bookType.getCategory(book->category), (book->isBorrow ? "借出" : "在册"));

    }

private:
    vector<Book::ptr> books; // 所有书籍
    map<string, int> stock; // 库存 <书名,数量>
    set<int> ids; // 编号集合
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
        printf("借书记录：\n");

        for (auto it = records.begin(); it != records.end(); ++it) {
            printf("    书籍编号:%d 书名:%s\n",(*it)->id,(*it)->bookName.c_str());
        }
    }

public:
    static int ids ;
    vector<Book::ptr> records; // 借书记录
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

    // 查询会员
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
            printf("会员编号:%d 姓名:%s\n",(*it)->myId,(*it)->name.c_str());
            (*it)->printRecords();
        }
    }

    void printAllMember()
    {
        printf("会员编号 姓名");
        for (auto it = members.begin(); it != members.end(); it++) {
            printf("%4d :%10s\n",(*it)->myId,(*it)->name.c_str());
        }
    }


    void printAllMemberRecord()
    {
        for (auto it = members.begin(); it != members.end(); it++) {
            printf("会员编号:%d 姓名:%s\n",(*it)->myId,(*it)->name.c_str());
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
    printf("会员管理功能：\n");
    printf("1.增加会员 \n");
    printf("2.删除会员 \n");
    printf("3.查询会员 \n");
    printf("4.查看所有会员 \n");
    printf("5.查看所有会员借书信息 \n");
    int n;
    cin >> n;
    if (n == 1) {
        printf("添加会员: 姓名\n");
        string name;
        cin >> name;
        Member::ptr member(new Member(name));
        printf("添加会员成功!\n");
    }else if(n == 2){
        printf("删除格式: ID\n");
        int memberId;
        cin >> memberId ;
        auto member = memberManager.find(memberId);
        memberManager.del(member);
    }else if(n == 3)
    {
        printf("查询格式: 姓名 ID\n");
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
    printf("图书借阅功能：\n");
    printf("1.增加图书 \n");
    printf("2.删除图书 \n");
    printf("3.查询图书 \n");
    printf("4.图书借阅 \n");
    printf("5.还书 \n");
    printf("6.查看所有书籍 \n");

    int n;
    cin >> n;
    if (n == 1) {
        printf("书籍格式: 编号 书名 作者 分类\n");
        Book book;
        cin >> book.id >> book.bookName >> book.author >> book.category;
        Book::ptr bookPtr;
        bookPtr.reset(&book);
        if (bookManager.add(bookPtr)) {
            printf("添加书籍成功!\n");
        } else printf("添加书籍失败!\n");

    } else if (n == 2) {
        printf("删除格式: 编号\n");
        int bookId;
        cin >> bookId;
        bookManager.del(bookId);
        if(bookManager.del(bookId)){
            printf("删除籍成功!\n");
        } else printf("删除书籍失败!\n");
    }else if(n == 3){
        printf("查询格式:  书名 作者 \n");
        Book book;
        cin >> book.bookName >> book.author;
        auto books = bookManager.query(book);
        bookManager.printBooks(books);
    }else if(n == 4)
    {
        printf("借阅格式: 图书编号 会员编号\n");
        int bookId,memberId;
        cin >> bookId >> memberId;
        Member::ptr member = memberManager.find(memberId);
        Book::ptr book = bookManager.find(bookId);
        if(book && member)
        {
            member->addRecord(book);
            printf("用户：%15s 借出 %25s\n",member->name.c_str(),book->bookName.c_str());
        }
    }else if(n == 5)
    {
        printf("还书格式: 图书编号\n");
        int bookId;
        cin >> bookId ;
        Book::ptr book = bookManager.find(bookId);
        if(book)
        {
            if(bookManager.backBook(book))
            {
                printf("还书成功!\n");
            } else printf("还书失败!\n");

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
    printf("图书借阅管理系统\n");
    printf("1.图书管理\n");
    printf("2.会员管理\n");
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
//    Book::ptr book(new Book("书名","作者",id++,'A'));
    for (int i = 0; i < 10; ++i) {
        bookManager.add(Book::ptr(new Book("书名" + to_string(i), to_string(i),id++,'A' + i)));
    }

    for (int i = 0; i < 10; ++i) {
        Member::ptr member(new Member("会员" + to_string(i)));
        memberManager.add(member);
        Book::ptr book;
        book = bookManager.find(6851+i);
        bookManager.borrowBook(book);
        member->addRecord(book);

    }

    beginUi();

    return 0;
}
