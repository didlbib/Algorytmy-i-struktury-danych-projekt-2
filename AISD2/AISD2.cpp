#include <cstdio>
#include <climits> // Dla INT_MAX

#define MAX_DIM  2005 
#define MAX_TOTAL_LIFTS 10005 
#define MAX_QUEUE (MAX_DIM * MAX_DIM) 

struct State {
    int time; 
    int x, y;   
};

State heap[MAX_QUEUE]; 
int heap_size = 0;     

// Funkcja dodaj¹ca element do kopca (utrzymuje w³asnoœæ kopca minimum)
void push(const State& s) {
    if (heap_size >= MAX_QUEUE) {
        // fprintf(stderr, "Heap overflow! Attempted to push state (time: %d, x: %d, y: %d) to full heap (size: %d).\n", s.time, s.x, s.y, heap_size);
        return;
    }
    int i = heap_size++;
    heap[i] = s;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].time <= heap[i].time) break;
        State tmp = heap[p];
        heap[p] = heap[i];
        heap[i] = tmp;
        i = p;
    }
}

// Funkcja usuwaj¹ca i zwracaj¹ca element o najmniejszym priorytecie (korzeñ kopca)
State pop() {
    State ret = heap[0];
    heap[0] = heap[--heap_size];

    int i = 0;
    while (true) {
        int left_child = i * 2 + 1;
        int right_child = i * 2 + 2;
        int smallest = i;

        if (left_child < heap_size && heap[left_child].time < heap[smallest].time) {
            smallest = left_child;
        }
        if (right_child < heap_size && heap[right_child].time < heap[smallest].time) {
            smallest = right_child;
        }

        if (smallest == i) break;

        State tmp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = tmp;
        i = smallest;
    }
    return ret;
}
// --- Koniec implementacji kolejki priorytetowej ---

// Struktura przechowuj¹ca informacje o windzie w globalnej tablicy
struct LiftInfo {
    int sx, sy;         
    int ex, ey;        
    int travel_time;    
    int interval;       
    int next_lift_idx; 
};

// Globalne tablice
int heights[MAX_DIM][MAX_DIM];
int dist[MAX_DIM][MAX_DIM];

LiftInfo all_lifts_storage[MAX_TOTAL_LIFTS]; 
int lift_head[MAX_DIM][MAX_DIM]; 
int current_lift_storage_idx = 0;

int width, height;

int main() {
    int start_x, start_y, end_x, end_y, n_lifts_total;

    scanf("%d%d", &width, &height);
    scanf("%d%d", &start_x, &start_y);
    scanf("%d%d", &end_x, &end_y);
    scanf("%d", &n_lifts_total);

    // Inicjalizacja lift_head
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            lift_head[y][x] = -1; // -1 oznacza brak wind z tego pola
        }
    }

    // Wczytywanie informacji o windach i budowanie list s¹siedztwa
    for (int i = 0; i < n_lifts_total; ++i) {
        int sx, sy, ex, ey, travel_time, interval_val; // Zmieniono nazwê interval na interval_val, aby unikn¹æ konfliktu
        scanf("%d%d%d%d%d%d", &sx, &sy, &ex, &ey, &travel_time, &interval_val);

        // Sprawdzenie poprawnoœci wspó³rzêdnych startowych i docelowych windy
        if (sx >= 0 && sx < width && sy >= 0 && sy < height &&
            ex >= 0 && ex < width && ey >= 0 && ey < height) {

            if (current_lift_storage_idx < MAX_TOTAL_LIFTS) {
                all_lifts_storage[current_lift_storage_idx].sx = sx;
                all_lifts_storage[current_lift_storage_idx].sy = sy;
                all_lifts_storage[current_lift_storage_idx].ex = ex;
                all_lifts_storage[current_lift_storage_idx].ey = ey;
                all_lifts_storage[current_lift_storage_idx].travel_time = travel_time;
                all_lifts_storage[current_lift_storage_idx].interval = interval_val;
                all_lifts_storage[current_lift_storage_idx].next_lift_idx = lift_head[sy][sx];
                lift_head[sy][sx] = current_lift_storage_idx;
                current_lift_storage_idx++;
            }
            else {
                // fprintf(stderr, "Warning: Exceeded MAX_TOTAL_LIFTS. Skipping lift.\n");
            }
        }
        else {
            // fprintf(stderr, "Warning: Invalid coordinates for a lift. Start (%d,%d) to End (%d,%d). Skipping lift.\n", sx, sy, ex, ey);
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            scanf("%d", &heights[y][x]);
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            dist[y][x] = INT_MAX;
        }
    }

    if (!(start_x >= 0 && start_x < width && start_y >= 0 && start_y < height &&
        end_x >= 0 && end_x < width && end_y >= 0 && end_y < height)) {
        printf("-1\n"); 
        return 0;
    }

    dist[start_y][start_x] = 0;
    heap_size = 0;
    push({ 0, start_x, start_y });

    int dirs[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

    while (heap_size > 0) {
        State s = pop();
        int time = s.time;
        int x = s.x;
        int y = s.y;

        if (x == end_x && y == end_y) {
            printf("%d\n", time);
            return 0;
        }

        if (time > dist[y][x]) {
            continue;
        }

        // Ruchy na s¹siednie pola
        for (int d = 0; d < 4; ++d) {
            int nx = x + dirs[d][0];
            int ny = y + dirs[d][1];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                int cost = 1;
                if (heights[ny][nx] > heights[y][x]) {
                    cost += heights[ny][nx] - heights[y][x];
                }
                if (dist[y][x] != INT_MAX && dist[y][x] + cost < dist[ny][nx]) {
                    if (dist[y][x] > INT_MAX - cost) { 
                        
                    }
                    else {
                        dist[ny][nx] = dist[y][x] + cost;
                        push({ dist[ny][nx], nx, ny });
                    }
                }
            }
        }

        int current_lift_idx = lift_head[y][x];
        while (current_lift_idx != -1) {
            LiftInfo& lift = all_lifts_storage[current_lift_idx];

            if (lift.interval <= 0) {
                current_lift_idx = lift.next_lift_idx;
                continue;
            }

            

            int wait_time = 0;
            if (time % lift.interval == 0) {
                wait_time = 0;
            }
            else {
                wait_time = lift.interval - (time % lift.interval);
            }

            
            int time_after_wait = time;
            if (time > INT_MAX - wait_time) { 
                current_lift_idx = lift.next_lift_idx; continue;
            }
            time_after_wait = time + wait_time;

            if (time_after_wait > INT_MAX - lift.travel_time) { 
                current_lift_idx = lift.next_lift_idx; continue;
            }
            int arrive_time = time_after_wait + lift.travel_time;

            if (arrive_time < dist[lift.ey][lift.ex]) {
                dist[lift.ey][lift.ex] = arrive_time;
                push({ arrive_time, lift.ex, lift.ey });
            }
            current_lift_idx = lift.next_lift_idx; 
        }
    }

    printf("-1\n");
    return 0;
}