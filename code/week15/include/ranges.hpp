namespace ranges {

class range {
  public:
    // this nested class is an iterator over the range
    class iterator {
      public:
        // we construct an iterator with the initial value for the iterate
        iterator(int x) : x_(x) {}

        // we increase the iterate
        auto operator++() {
            ++x_;
            return this;
        }

        // dereferencing the iterator simply returns the iterate
        auto operator*() { return x_; }

        // two iterators are unequal iff their iterates are unequal
        bool operator!=(iterator& other) { return x_ != other.x_; }

      private:
        // the state of the iterator: the current value of the iterate
        int x_ = 0;
    };

    // range(n) is a virtual container with elements { 0, ...,  n - 1 }
    range(int n) : n_(n) {}

    // the beginning of the range is 0
    auto begin() { return iterator(0); }
    // the end of the range is n
    auto end() { return iterator(n_); }

  private:
    int n_ = 0;
};

} // namespace ranges
