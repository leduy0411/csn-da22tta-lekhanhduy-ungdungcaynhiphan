#include <iostream>
#include <string>
using namespace std;

//cau truc cua 1 nhan vien. 
struct Employee {
    int id;
    string name;
    double salary;
};

//1 node cua cay nhi phan. 
struct Node {
    Employee emp;
    Node* left;
    Node* right;

    // Constructor: de khoi tao node moi. 
    Node(Employee e) : emp(e), left(NULL), right(NULL) {}
};

// ham de them nhan vien vao cay nhi phan 
Node* insertNode(Node* root, Employee emp) {
    if (root == NULL) {
        return new Node(emp);
    }

    // Neu ID cua nhan vien < ID cua node hien tai , them vao ben trai. 
    if (emp.id < root->emp.id) {
        root->left = insertNode(root->left, emp);
    }
    // Neu ID cua nhan vien > ID cua node hien tai , them vao ben phai. 
    else {
        root->right = insertNode(root->right, emp);
    }

    return root;
}

// Ham inorder de duyet cay nhi phan ( trai - node - phai) 
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        cout << "ID: " << root->emp.id << ", Ten: " << root->emp.name << ", Luong: " << root->emp.salary << endl;
        inorderTraversal(root->right);
    }
}

// Ham tim kiem nhan vien theo ID. 
Node* searchEmployeeByID(Node* root, int id) {
    if (root == NULL || root->emp.id == id) {
        return root;
    }

    if (id < root->emp.id) {
        return searchEmployeeByID(root->left, id);
    } else {
        return searchEmployeeByID(root->right, id);
    }
}

// Ham tim kiem nhan vien theo ten. 
Node* searchEmployeeByName(Node* root, const string& name) {
    if (root == NULL) {
        return NULL;
    }

    if (root->emp.name == name) {
        return root;
    }

    Node* leftSearch = searchEmployeeByName(root->left, name);
    if (leftSearch != NULL) {
        return leftSearch;
    }

    return searchEmployeeByName(root->right, name);
}

// Ham xoa nhan vien ra khoi cay (theo ID)
Node* deleteNode(Node* root, int id) {
    if (root == NULL) {
        return root;
    }

    // Neu ID can xoa > ID cua node hien tai, di sang cay con ben trai. 
    if (id < root->emp.id) {
        root->left = deleteNode(root->left, id);
    }
    // Neu ID can xoa < ID cua node hien tai, di sang cay con ben phai. 
    else if (id > root->emp.id) {
        root->right = deleteNode(root->right, id);
    }
    // Neu ID tim thay tai node hien tai. 
    else {
        // Node chi co 1 hoac khong con. 
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node co hai con. 
        Node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        root->emp = temp->emp; // sao chep gia chi cua node ke tiep nho nhat. 
        root->right = deleteNode(root->right, temp->emp.id); // Xóa node k? ti?p nh? nh?t
    }
    return root;
}

// Ham sua thong tin nhan vien theo ID. 
void updateEmployee(Node* root, int id, string newName, double newSalary) {
    Node* employeeNode = searchEmployeeByID(root, id);
    if (employeeNode != NULL) {
        employeeNode->emp.name = newName;
        employeeNode->emp.salary = newSalary;
        cout << "Thong tin nhan vien voi ID " << id << " da duoc cap nhat.\n";
    } else {
        cout << "Khong tim thay nhan vien voi ID " << id << endl;
    }
}

// Ham nhap thong tin nhan vien tu ban phim. 
Employee inputEmployee() {
    Employee emp;
    cout << "Nhap ID nhan vien : ";
    cin >> emp.id;
    cin.ignore(); 
    cout << "Nhap ten nhan vien : ";
    getline(cin, emp.name);
    cout << "Nhap luong nhan vien : ";
    cin >> emp.salary;
    return emp;
}

// Ham nhap lua chon theo nhu cau. 
void menu() {
    cout << "\n======== MENU ========\n";
    cout << "1. Them nhan vien\n";
    cout << "2. Xoa nhan vien\n";
    cout << "3. Sua thong tin nhan vien\n";
    cout << "4. Hien thi danh sach nhan vien\n";
    cout << "5. Tim kiem nhan vien theo ID\n";
    cout << "6. Tim kiem nhan vien theo ten\n";
    cout << "7. Thoat\n";
    cout << "=====================\n";
    cout << "Lua chon cua ban: ";
}

int main() {
    Node* root = NULL;
    int choice;
    int id;
    string name;
    double salary;

    while (true) {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: {
                // Them nhan vien. 
                Employee emp = inputEmployee();
                root = insertNode(root, emp);
                cout << "Da them nhan vien voi ID: " << emp.id << endl;
                break;
            }
            case 2: {
                //Xoa nhan vien. 
                cout << "Nhap ID cua nhan vien can xoa: ";
                cin >> id;
                root = deleteNode(root, id);
                cout << "Da xoa nhan vien voi ID: " << id << endl;
                break;
            }
            case 3: {
                // Sua thong tin nhan vien. 
                cout << "Nhap ID cua nhan vien can sua: ";
                cin >> id;
                cin.ignore();
                cout << "Nhap ten moi: ";
                getline(cin, name);
                cout << "Nhap luong moi: ";
                cin >> salary;
                updateEmployee(root, id, name, salary);
                break;
            }
            case 4: {
                // Hien thi danh sach nhan vien. 
                cout << "\nDanh sach nhan vien:\n";
                inorderTraversal(root);
                break;
            }
            case 5: {
                // Tim kiem nhan vien theo ID. 
                cout << "Nhap ID nhan vien can tim: ";
                cin >> id;
                Node* foundByID = searchEmployeeByID(root, id);
                if (foundByID != NULL) {
                    cout << "Tim thay nhan vien: ID: " << foundByID->emp.id << ", Ten: " << foundByID->emp.name << ", Luong: " << foundByID->emp.salary << endl;
                } else {
                    cout << "Khong tim thay nhan vien voi ID " << id << endl;
                }
                break;
            }
            case 6: {
                // Tim kiem nhan vien theo ten. 
                cout << "Nhap ten nhan vien can tim: ";
                cin.ignore();
                getline(cin, name);
                Node* foundByName = searchEmployeeByName(root, name);
                if (foundByName != NULL) {
                    cout << "Tim thay nhan vien: ID: " << foundByName->emp.id << ", Ten: " << foundByName->emp.name << ", Luong: " << foundByName->emp.salary << endl;
                } else {
                    cout << "Khong tim thay nhan vien voi ten " << name << endl;
                }
                break;
            }
            case 7: {
                // Thoat 
                cout << "Thanks ban da su dung chuong trinh!\n";
                return 0;
            }
            default:
                cout << "Lua chon khong hop le! vui long chon lai.\n";
        }
    }

    return 0;
}

