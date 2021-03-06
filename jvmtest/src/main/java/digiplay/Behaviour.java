package digiplay;

public class Behaviour {

    public Sprite parent;
    public Behaviour next;

    public void setParent(Sprite value) {
        if (parent != null) {
            dispose();
        }

        parent = value;
        if (parent != null) {
            startTime = Platform.gameTime;
            markedForRemoval = false;
            isInterrupted = false;
            init();
        }
    }

    public float startTime = 0;
    public boolean markedForRemoval;
    public boolean isInterrupted;

    public void dispose() {
    }

    public void init() {
    }

    public boolean update(float time) {
        return true;
    }

    public boolean isRunning() {
        return parent != null && !markedForRemoval;
    }

}
