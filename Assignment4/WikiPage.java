//  This code written by someone else.
//  Attribution info stripped to make software usable for CS 511.

class WikiPage extends Page {
    private String title;
    private String text;

    public WikiPage(String title, String text) { this.title = title; this.text = text; }

    public String getTitle() { return title; }
    public String getText() { return text; }
}
