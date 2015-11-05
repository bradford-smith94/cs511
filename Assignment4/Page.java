//  This code written by someone else.
//  Attribution info stripped to make software usable for CS 511.

abstract class Page {
    public String getTitle() { throw new UnsupportedOperationException(); }
    public String getText() { throw new UnsupportedOperationException(); }
    public boolean isPoisonPill() { return false; }
}
