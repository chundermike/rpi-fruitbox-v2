#pragma once

class PlayQueueClass {
public:
  void Load(const string filename);
  void Save(const string filename);
  bool FindSong(song_t *song);
  song_t * QuerySong(const int32_t from_top);
  bool Add(song_t *song, play_type_e play_type);
  void Remove(void);
  void Clear(void);
  uint32_t NumSongsTotal(void);
  uint32_t NumSongsComingUp(void);
  string NumSongsComingUpStr(void);
  string TotalTimeComingUp(void);
  string RemainingSpaceStr(void);
  std::mutex mtx;
  void AddToHistory(const int32_t from_top);
  deque<song_t *> song_play_history { };
  deque<song_t*> queue { };
  bool empty {true};
  bool full {false};
  float occupancy {0}; // 0 to 1 (100%)
  atomic<int32_t>status_event;
private:
  uint32_t total_time { };
};
