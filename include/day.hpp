template <typename Day>
class Solver
{
    Day &impl() { return *static_cast<Day *>(this); }

public:
    void solve() { impl().solve(); }
};
