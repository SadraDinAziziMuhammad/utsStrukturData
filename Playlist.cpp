#include <iostream>
#include <string>
using namespace std;

struct Podcast {
    string judul;
    int durasi;
    string kategori;
    Podcast* next;
    Podcast* prev;

    Podcast(string j, int d, string k) {
        judul = j;
        durasi = d;
        kategori = k;
        next = nullptr;
        prev = nullptr;
    }
};

class Playlist {
private:
    Podcast* head;
    Podcast* tail;
    Podcast* current;

public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}

    void tambahPodcast(string judul, int durasi, string kategori) {
        Podcast* baru = new Podcast(judul, durasi, kategori);
        if (!head) {
            head = tail = current = baru;
        } else {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        }
        cout << "✅ Podcast \"" << judul << "\" berhasil ditambahkan.\n";
    }

    void sisipkanPodcast(string setelahJudul, string judul, int durasi, string kategori) {
        Podcast* temp = head;
        while (temp && temp->judul != setelahJudul) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "⚠️  Judul \"" << setelahJudul << "\" tidak ditemukan.\n";
            return;
        }

        Podcast* baru = new Podcast(judul, durasi, kategori);
        baru->next = temp->next;
        baru->prev = temp;

        if (temp->next) {
            temp->next->prev = baru;
        } else {
            tail = baru;
        }

        temp->next = baru;
        cout << "✅ Podcast \"" << judul << "\" berhasil disisipkan.\n";
    }

    void hapusPodcast(string judul) {
        Podcast* temp = head;
        while (temp && temp->judul != judul) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "⚠️  Podcast \"" << judul << "\" tidak ditemukan.\n";
            return;
        }

        if (temp == head) head = head->next;
        if (temp == tail) tail = tail->prev;

        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;

        if (current == temp) current = head;

        delete temp;
        cout << "🗑️  Podcast \"" << judul << "\" telah dihapus.\n";
    }

    void nextPodcast() {
        if (current && current->next) {
            current = current->next;
            tampilkanPodcastSaatIni();
        } else {
            cout << "⚠️  Tidak ada podcast berikutnya.\n";
        }
    }

    void prevPodcast() {
        if (current && current->prev) {
            current = current->prev;
            tampilkanPodcastSaatIni();
        } else {
            cout << "⚠️  Tidak ada podcast sebelumnya.\n";
        }
    }

    void tampilkanPodcastSaatIni() {
        if (current) {
            cout << "\n🎧 Sedang diputar:\n";
            cout << "Judul   : " << current->judul << endl;
            cout << "Durasi  : " << current->durasi << " menit\n";
            cout << "Kategori: " << current->kategori << "\n";
        } else {
            cout << "⚠️  Tidak ada podcast yang sedang diputar.\n";
        }
    }

    void tampilkanPlaylistForward() {
        Podcast* temp = head;
        if (!temp) {
            cout << "📂 Playlist kosong.\n";
            return;
        }

        cout << "\n📜 Playlist (Depan ke Belakang):\n";
        while (temp) {
            cout << "- " << temp->judul << " (" << temp->durasi << " menit, " << temp->kategori << ")\n";
            temp = temp->next;
        }
    }

    void tampilkanPlaylistBackward() {
        Podcast* temp = tail;
        if (!temp) {
            cout << "📂 Playlist kosong.\n";
            return;
        }

        cout << "\n📜 Playlist (Belakang ke Depan):\n";
        while (temp) {
            cout << "- " << temp->judul << " (" << temp->durasi << " menit, " << temp->kategori << ")\n";
            temp = temp->prev;
        }
    }
};

void tampilkanMenu() {
    cout << "\n====== MENU PODCAST KAMPUS ======\n";
    cout << "1. Tambah podcast ke akhir playlist\n";
    cout << "2. Sisipkan podcast setelah judul tertentu\n";
    cout << "3. Hapus podcast berdasarkan judul\n";
    cout << "4. Putar podcast berikutnya\n";
    cout << "5. Putar podcast sebelumnya\n";
    cout << "6. Tampilkan playlist (depan ke belakang)\n";
    cout << "7. Tampilkan playlist (belakang ke depan)\n";
    cout << "8. Tampilkan podcast saat ini\n";
    cout << "9. Keluar\n";
    cout << "Pilih menu: ";
}

int main() {
    Playlist playlist;
    int pilihan;
    string judul, kategori, setelahJudul;
    int durasi;

    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(); // agar getline() tidak error setelah cin

        switch (pilihan) {
            case 1:
                cout << "Masukkan judul podcast: ";
                getline(cin, judul);
                cout << "Masukkan durasi (menit): ";
                cin >> durasi;
                cin.ignore();
                cout << "Masukkan kategori: ";
                getline(cin, kategori);
                playlist.tambahPodcast(judul, durasi, kategori);
                break;

            case 2:
                cout << "Masukkan judul podcast yang ingin disisipkan setelahnya: ";
                getline(cin, setelahJudul);
                cout << "Masukkan judul podcast baru: ";
                getline(cin, judul);
                cout << "Masukkan durasi (menit): ";
                cin >> durasi;
                cin.ignore();
                cout << "Masukkan kategori: ";
                getline(cin, kategori);
                playlist.sisipkanPodcast(setelahJudul, judul, durasi, kategori);
                break;

            case 3:
                cout << "Masukkan judul podcast yang ingin dihapus: ";
                getline(cin, judul);
                playlist.hapusPodcast(judul);
                break;

            case 4:
                playlist.nextPodcast();
                break;

            case 5:
                playlist.prevPodcast();
                break;

            case 6:
                playlist.tampilkanPlaylistForward();
                break;

            case 7:
                playlist.tampilkanPlaylistBackward();
                break;

            case 8:
                playlist.tampilkanPodcastSaatIni();
                break;

            case 9:
                cout << "👋 Keluar dari program. Terima kasih!\n";
                break;

            default:
                cout << "❌ Pilihan tidak valid. Coba lagi.\n";
                break;
        }
    } while (pilihan != 9);

    return 0;
}
